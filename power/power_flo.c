/*
 * Copyright (C) 2014 The Android Open Source Project
 * Copyright (C) 2016 The CyanogenMod Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <cutils/uevent.h>
#include <errno.h>
#include <sys/poll.h>
#include <pthread.h>
#include <linux/netlink.h>
#include <stdlib.h>
#include <stdbool.h>

#define LOG_TAG "PowerHAL"
#include <utils/Log.h>

#include <hardware/hardware.h>
#include <hardware/power.h>

#define STATE_ON "state=1"
#define STATE_OFF "state=0"

#define MAX_LENGTH         50
#define BOOST_SOCKET       "/dev/socket/pb"

#define LOW_POWER_MAX_FREQ "1026000"
#define LOW_POWER_MIN_FREQ "384000"
#define NORMAL_MAX_FREQ "1512000"

#define MAX_FREQ_LIMIT_PATH "/sys/kernel/cpufreq_limit/limited_max_freq"
#define MIN_FREQ_LIMIT_PATH "/sys/kernel/cpufreq_limit/limited_min_freq"

#define TIMER_RATE_INTERACTIVE "20000"
#define TIMER_RATE_SUSPEND "50000"

#define TIMER_RATE_PATH "/sys/devices/system/cpu/cpufreq/interactive/timer_rate"

static int client_sockfd;
static struct sockaddr_un client_addr;
static int last_state = -1;

static pthread_mutex_t hint_mutex = PTHREAD_MUTEX_INITIALIZER;

enum {
    PROFILE_POWER_SAVE = 0,
    PROFILE_BALANCED,
    PROFILE_HIGH_PERFORMANCE,
    PROFILE_BIAS_POWER,
    PROFILE_BIAS_PERFORMANCE
};

static int current_power_profile = PROFILE_BALANCED;

static unsigned int target_min_freq = LOW_POWER_MIN_FREQ;
static unsigned int target_max_freq = NORMAL_MAX_FREQ;

static void socket_init()
{
    if (!client_sockfd) {
        client_sockfd = socket(PF_UNIX, SOCK_DGRAM, 0);
        if (client_sockfd < 0) {
            ALOGE("%s: failed to open: %s", __func__, strerror(errno));
            return;
        }
        memset(&client_addr, 0, sizeof(struct sockaddr_un));
        client_addr.sun_family = AF_UNIX;
        snprintf(client_addr.sun_path, UNIX_PATH_MAX, BOOST_SOCKET);
    }
}

static int sysfs_write(const char *path, char *s)
{
    char buf[80];
    int len;
    int fd = open(path, O_WRONLY);

    if (fd < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error opening %s: %s\n", path, buf);
        return -1;
    }

    len = write(fd, s, strlen(s));
    if (len < 0) {
        strerror_r(errno, buf, sizeof(buf));
        ALOGE("Error writing to %s: %s\n", path, buf);
        return -1;
    }

    close(fd);
    return 0;
}

static void power_init(__attribute__((unused)) struct power_module *module)
{
    ALOGI("%s", __func__);
    socket_init();
}

static void enc_boost(int off)
{
    int rc;
    pid_t client;
    char data[MAX_LENGTH];

    if (client_sockfd < 0) {
        ALOGE("%s: boost socket not created", __func__);
        return;
    }

    client = getpid();

    if (!off) {
        snprintf(data, MAX_LENGTH, "5:%d", client);
        rc = sendto(client_sockfd, data, strlen(data), 0,
            (const struct sockaddr *)&client_addr, sizeof(struct sockaddr_un));
    } else {
        snprintf(data, MAX_LENGTH, "6:%d", client);
        rc = sendto(client_sockfd, data, strlen(data), 0,
            (const struct sockaddr *)&client_addr, sizeof(struct sockaddr_un));
    }

    if (rc < 0) {
        ALOGE("%s: failed to send: %s", __func__, strerror(errno));
    }
}

static void process_video_encode_hint(void *metadata)
{

    socket_init();

    if (client_sockfd < 0) {
        ALOGE("%s: boost socket not created", __func__);
        return;
    }

    if (metadata) {
        if (!strncmp(metadata, STATE_ON, sizeof(STATE_ON))) {
            /* Video encode started */
            enc_boost(1);
        } else if (!strncmp(metadata, STATE_OFF, sizeof(STATE_OFF))) {
            /* Video encode stopped */
            enc_boost(0);
        }
    }
}

static void touch_boost()
{
    int rc;
    pid_t client;
    char data[MAX_LENGTH];

    if (client_sockfd < 0) {
        ALOGE("%s: boost socket not created", __func__);
        return;
    }

    client = getpid();

    snprintf(data, MAX_LENGTH, "1:%d", client);
    rc = sendto(client_sockfd, data, strlen(data), 0,
        (const struct sockaddr *)&client_addr, sizeof(struct sockaddr_un));
    if (rc < 0) {
        ALOGE("%s: failed to send: %s", __func__, strerror(errno));
    }
}

static void power_set_interactive(__attribute__((unused)) struct power_module *module, int on)
{
    if (last_state == -1) {
        last_state = on;
    } else {
        if (last_state == on)
            return;
        else
            last_state = on;
    }

    ALOGD("%s %s", __func__, (on ? "ON" : "OFF"));
    if (on) {
        touch_boost();
    }

    sysfs_write(TIMER_RATE_PATH, on ? TIMER_RATE_INTERACTIVE : TIMER_RATE_SUSPEND);
}

static void set_power_profile(int profile)
{
    if (profile == current_power_profile)
        return;

    ALOGV("%s: profile=%d", __func__, profile);

    if (profile == PROFILE_BALANCED) {
        target_min_freq = LOW_POWER_MIN_FREQ;
        target_max_freq = NORMAL_MAX_FREQ;
        ALOGD("%s: set balanced mode", __func__);
    } else if (profile == PROFILE_HIGH_PERFORMANCE) {
        target_min_freq = NORMAL_MAX_FREQ;
        target_max_freq = NORMAL_MAX_FREQ;
        ALOGD("%s: set performance mode", __func__);
    } else if (profile == PROFILE_BIAS_PERFORMANCE) {
        target_min_freq = LOW_POWER_MAX_FREQ;
        target_max_freq = NORMAL_MAX_FREQ;
        ALOGD("%s: set bias perf mode", __func__);
    } else if (profile == PROFILE_BIAS_POWER) {
        target_min_freq = LOW_POWER_MIN_FREQ;
        target_max_freq = LOW_POWER_MAX_FREQ;
        ALOGD("%s: set bias power mode", __func__);
    } else if (profile == PROFILE_POWER_SAVE) {
        target_min_freq = LOW_POWER_MIN_FREQ;
        target_max_freq = LOW_POWER_MAX_FREQ;
        ALOGD("%s: set powersave", __func__);
    }

    sysfs_write(MIN_FREQ_LIMIT_PATH, target_min_freq);
    sysfs_write(MAX_FREQ_LIMIT_PATH, target_max_freq);

    current_power_profile = profile;
}

static void power_hint( __attribute__((unused)) struct power_module *module,
                      power_hint_t hint, void *data)
{
    if (hint == POWER_HINT_SET_PROFILE) {
        pthread_mutex_lock(&hint_mutex);
        set_power_profile(*(int32_t *) data);
        pthread_mutex_unlock(&hint_mutex);
        return;
    }

    // Skip other hints in low power mode
    if (current_power_profile == PROFILE_POWER_SAVE)
        return;

    switch (hint) {
        case POWER_HINT_LAUNCH_BOOST:
        case POWER_HINT_CPU_BOOST:
            touch_boost();
            break;
        case POWER_HINT_VIDEO_ENCODE:
            process_video_encode_hint(data);
            break;
        default:
            break;
    }
}

static struct hw_module_methods_t power_module_methods = {
    .open = NULL,
};

int get_feature(struct power_module *module __unused, feature_t feature)
{
    if (feature == POWER_FEATURE_SUPPORTED_PROFILES) {
        return 5;
    }

    return -1;
}

struct power_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = POWER_MODULE_API_VERSION_0_2,
        .hal_api_version = HARDWARE_HAL_API_VERSION,
        .id = POWER_HARDWARE_MODULE_ID,
        .name = "Flo/Deb Power HAL",
        .author = "The Android Open Source Project / The CyanogenMod Project",
        .methods = &power_module_methods,
    },

    .init = power_init,
    .setInteractive = power_set_interactive,
    .powerHint = power_hint,
    .getFeature = get_feature
};
