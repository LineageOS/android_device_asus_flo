/*
 * Copyright (C) 2014 The Android Open Source Project
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

#define UEVENT_MSG_LEN 2048
#define TOTAL_CPUS 4
#define RETRY_TIME_CHANGING_FREQ 20
#define SLEEP_USEC_BETWN_RETRY 200
#define LOW_POWER_MAX_FREQ "1026000"
#define LOW_POWER_MIN_FREQ "384000"
#define NORMAL_MAX_FREQ "1512000"
#define UEVENT_STRING "online@/devices/system/cpu/"

static int client_sockfd;
static struct sockaddr_un client_addr;
static int last_state = -1;

static struct pollfd pfd;
static char *cpu_path_min[] = {
    "/sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq",
    "/sys/devices/system/cpu/cpu1/cpufreq/scaling_min_freq",
    "/sys/devices/system/cpu/cpu2/cpufreq/scaling_min_freq",
    "/sys/devices/system/cpu/cpu3/cpufreq/scaling_min_freq",
};
static char *cpu_path_max[] = {
    "/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq",
    "/sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq",
    "/sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq",
    "/sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq",
};
static pthread_mutex_t perf_profile_lock = PTHREAD_MUTEX_INITIALIZER;

static int target_min_freq = LOW_POWER_MIN_FREQ;
static int target_max_freq = NORMAL_MAX_FREQ;

enum {
    PROFILE_POWER_SAVE = 0,
    PROFILE_BALANCED,
    PROFILE_HIGH_PERFORMANCE
};

static int current_power_profile = PROFILE_BALANCED;

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

static int uevent_event()
{
    char msg[UEVENT_MSG_LEN];
    char *cp;
    int n, cpu, ret, retry = RETRY_TIME_CHANGING_FREQ;

    n = recv(pfd.fd, msg, UEVENT_MSG_LEN, MSG_DONTWAIT);
    if (n <= 0) {
        return -1;
    }
    if (n >= UEVENT_MSG_LEN) {   /* overflow -- discard */
        return -1;
    }

    cp = msg;

    if (strstr(cp, UEVENT_STRING)) {
        n = strlen(cp);
        errno = 0;
        cpu = strtol(cp + n - 1, NULL, 10);

        if (errno == EINVAL || errno == ERANGE || cpu < 0 || cpu >= TOTAL_CPUS) {
            return -1;
        }

        pthread_mutex_lock(&perf_profile_lock);
        while (retry) {
            sysfs_write(cpu_path_min[cpu], target_min_freq);
            ret = sysfs_write(cpu_path_max[cpu], target_max_freq);
            if (!ret) {
                break;
            }
            usleep(SLEEP_USEC_BETWN_RETRY);
            retry--;
        }
        pthread_mutex_unlock(&perf_profile_lock);
    }
    return 0;
}

void *thread_uevent(__attribute__((unused)) void *x)
{
    while (1) {
        int nevents, ret;

        nevents = poll(&pfd, 1, -1);

        if (nevents == -1) {
            if (errno == EINTR)
                continue;
            ALOGE("powerhal: thread_uevent: poll_wait failed\n");
            break;
        }
        ret = uevent_event();
        if (ret < 0)
            ALOGE("Error processing the uevent event");
    }
    return NULL;
}

static void uevent_init()
{
    struct sockaddr_nl client;
    pthread_t tid;
    pfd.fd = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);

    if (pfd.fd < 0) {
        ALOGE("%s: failed to open: %s", __func__, strerror(errno));
        return;
    }
    memset(&client, 0, sizeof(struct sockaddr_nl));
    pthread_create(&tid, NULL, thread_uevent, NULL);
    client.nl_family = AF_NETLINK;
    client.nl_pid = tid;
    client.nl_groups = -1;
    pfd.events = POLLIN;
    bind(pfd.fd, (void *)&client, sizeof(struct sockaddr_nl));
    return;
}

static void power_init(__attribute__((unused)) struct power_module *module)
{
    ALOGI("%s", __func__);
    socket_init();
    uevent_init();
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

    if (current_power_profile != PROFILE_BALANCED)
        return;

    ALOGV("%s %s", __func__, (on ? "ON" : "OFF"));
    if (on) {
        touch_boost();
    }
}

static void set_power_profile(int profile)
{
    int cpu;

    if (profile == current_power_profile)
        return;

    ALOGV("%s: profile=%d", __func__, profile);

    pthread_mutex_lock(&perf_profile_lock);

    if (profile == PROFILE_BALANCED) {
        target_min_freq = LOW_POWER_MIN_FREQ;
        target_max_freq = NORMAL_MAX_FREQ;
        ALOGD("%s: set balanced mode", __func__);
    } else if (profile == PROFILE_HIGH_PERFORMANCE) {
        target_min_freq = NORMAL_MAX_FREQ;
        target_max_freq = NORMAL_MAX_FREQ;
        ALOGD("%s: set performance mode", __func__);
    } else if (profile == PROFILE_POWER_SAVE) {
        target_min_freq = LOW_POWER_MIN_FREQ;
        target_max_freq = LOW_POWER_MAX_FREQ;
        ALOGD("%s: set powersave", __func__);
    }

    for (cpu = 0; cpu < TOTAL_CPUS; cpu++) {
        sysfs_write(cpu_path_min[cpu], target_min_freq);
        sysfs_write(cpu_path_max[cpu], target_max_freq);
    }

    pthread_mutex_unlock(&perf_profile_lock);

    current_power_profile = profile;
}

static void power_hint( __attribute__((unused)) struct power_module *module,
                      power_hint_t hint, void *data)
{
    switch (hint) {
        case POWER_HINT_INTERACTION:
            if (current_power_profile != PROFILE_BALANCED)
                return;
            ALOGV("POWER_HINT_INTERACTION");
            touch_boost();
            break;
        case POWER_HINT_VIDEO_ENCODE:
            if (current_power_profile != PROFILE_BALANCED)
                return;
            process_video_encode_hint(data);
            break;
        case POWER_HINT_SET_PROFILE:
            set_power_profile(*(int32_t *)data);
            break;
        case POWER_HINT_LOW_POWER:
            if (current_power_profile == PROFILE_POWER_SAVE)
                set_power_profile(PROFILE_BALANCED);
            else
                set_power_profile(PROFILE_POWER_SAVE);
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
        return 3;
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
        .author = "The Android Open Source Project",
        .methods = &power_module_methods,
    },

    .init = power_init,
    .setInteractive = power_set_interactive,
    .powerHint = power_hint,
    .getFeature = get_feature
};
