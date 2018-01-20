/*
 * Copyright (C) 2018 Unlegacy Android Project
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

#include <cutils/log.h>
#include <hardware/sensors.h>
#include <string>
#include <dlfcn.h>
#include <errno.h>

// The "real" sensor lib to wrap around
#define SENSOR_LIB "sensors.flo.so"

// Enable experimental flush support
#define FLUSH_SUPPORT

static void *lib_handle = NULL;
static struct sensors_module_t *lib_sensors_module;
static struct hw_device_t *lib_hw_device;
static sensors_poll_device_1_t dev;

// Copy of the original sensors list with the fixed properties
static const struct sensor_t *global_sensors_list = NULL;

#ifdef FLUSH_SUPPORT
static bool flush_requested = false;
static int32_t flush_requested_sensors = 0;
static pthread_mutex_t flush_lock = PTHREAD_MUTEX_INITIALIZER;
#endif

static int open_lib()
{
    if (lib_handle != NULL)
        return 0;

    lib_handle = dlopen(SENSOR_LIB, RTLD_LAZY);
    if (lib_handle == NULL) {
        ALOGW("dlerror(): %s", dlerror());
        return -EINVAL;
    } else {
        const char *sym = HAL_MODULE_INFO_SYM_AS_STR;
        ALOGV("Loaded library %s", SENSOR_LIB);
        ALOGV("Opening symbol \"%s\"", sym);
        // clear old errors
        dlerror();
        lib_sensors_module = (sensors_module_t *) dlsym(lib_handle, sym);
        const char* error;
        if ((error = dlerror()) != NULL) {
            ALOGE("Error calling dlsym: %s", error);
            dlclose(lib_handle);
            return -EINVAL;
        } else {
            ALOGV("Loaded symbols from \"%s\"", sym);
        }
    }

    return 0;
}

static int get_sensor_index_from_handle(int handle)
{
    // we're expected to always succeed here
    for (int i = 0; /* no condition */; ++i) {
        if (global_sensors_list[i].handle == handle)
            return i;
    }
    return -1;
}

static int sensors_get_sensors_list(struct sensors_module_t *module __unused,
    struct sensor_t const** sensors_list)
{
    int ret = open_lib();
    if (ret < 0)
        return 0;

    int sensors_count =
        lib_sensors_module->get_sensors_list(lib_sensors_module, sensors_list);

    // sensors_list is full of consts - Manipulate this non-const list,
    // and point the const one to it when we're done.
    sensor_t *mutable_sensor_list = new sensor_t[sensors_count];
    memcpy(mutable_sensor_list, *sensors_list,
        sizeof(struct sensor_t) * sensors_count);
    global_sensors_list = mutable_sensor_list;
    *sensors_list = global_sensors_list;

    // fix sensor properties
    for (int i = 0; i < sensors_count; ++i) {
        sensor_t *sensor = &mutable_sensor_list[i];
        if (sensor->type == SENSOR_TYPE_PROXIMITY)
            sensor->flags = SENSOR_FLAG_WAKE_UP | SENSOR_FLAG_ON_CHANGE_MODE;
        else if (sensor->type == SENSOR_TYPE_SIGNIFICANT_MOTION)
            sensor->flags = SENSOR_FLAG_WAKE_UP | SENSOR_FLAG_ONE_SHOT_MODE;
        else
            sensor->maxDelay = 1000000; // 1 sec
    }

    return sensors_count;
}

static int sensor_device_close(struct hw_device_t *dev __unused)
{
    lib_hw_device->close(lib_hw_device);
    dlclose(lib_handle);
    lib_handle = NULL;
    delete[] global_sensors_list;

    return 0;
}

static int sensor_device_activate(struct sensors_poll_device_t *dev __unused,
     int handle, int enabled)
{
    struct sensors_poll_device_t *mod =
        (struct sensors_poll_device_t *) lib_hw_device;
    ALOGV("%s: handle=%d enabled=%d", __func__, handle, enabled);
    return mod->activate(mod, handle,enabled);
}

static int sensor_device_set_delay(struct sensors_poll_device_t *dev __unused,
    int handle, int64_t ns)
{
    struct sensors_poll_device_t *mod =
        (struct sensors_poll_device_t *) lib_hw_device;
    return mod->setDelay(mod, handle, ns);
}

static int sensor_device_poll(struct sensors_poll_device_t *dev __unused,
    sensors_event_t* data, int count)
{
    struct sensors_poll_device_t *mod =
        (struct sensors_poll_device_t *) lib_hw_device;

    int num_events = mod->poll(mod, data, count);

    for (int i = 0; i < num_events; ++i) {
        ALOGV("%s: received event type=%d timestamp=%lld",
            __func__, data[i].type, data[i].timestamp);
    }

#ifdef FLUSH_SUPPORT
    pthread_mutex_lock(&flush_lock);
    if (flush_requested && num_events < count) {
        ALOGV("%s: adding flush event", __func__);
        flush_requested = false;
        data[num_events].version = META_DATA_VERSION;
        data[num_events].type = SENSOR_TYPE_META_DATA;
        data[num_events].sensor = 0;
        data[num_events].timestamp = 0;
        data[num_events].meta_data.what = META_DATA_FLUSH_COMPLETE;
        data[num_events].meta_data.sensor = flush_requested_sensors;
        flush_requested_sensors = 0;
        ++num_events;
    }
    pthread_mutex_unlock(&flush_lock);
#endif

    ALOGV("%s: returning %d events", __func__, num_events);

    return num_events;
}

static int sensor_device_batch(struct sensors_poll_device_1 *dev __unused,
    int handle, int flags __unused, int64_t period_ns, int64_t timeout __unused)
{
    struct sensors_poll_device_t *mod =
        (struct sensors_poll_device_t *) lib_hw_device;

    int sensor_index = get_sensor_index_from_handle(handle);
    int maxDelay = global_sensors_list[sensor_index].maxDelay;
    int minDelay = global_sensors_list[sensor_index].minDelay;
    if (period_ns < minDelay) {
        period_ns = minDelay;
    } else if (period_ns > maxDelay * 1000) {
        period_ns = maxDelay * 1000;
    }

    ALOGV("%s: handle=%d type=%d maxDelay=%d minDelay=%d, delay set to %lld",
        __func__, handle, global_sensors_list[sensor_index].type,
        maxDelay, minDelay, period_ns);

    return mod->setDelay(mod, handle, period_ns);
}

static int sensor_device_flush(struct sensors_poll_device_1 *dev __unused,
    int sensor_handle)
{
#ifdef FLUSH_SUPPORT
    pthread_mutex_lock(&flush_lock);
    flush_requested = true;
    flush_requested_sensors |= sensor_handle;
    pthread_mutex_unlock(&flush_lock);
    return 0;
#else
    return -EINVAL;
#endif
}

static int open_sensors(const struct hw_module_t *hw_module, const char *name,
    struct hw_device_t **hw_device_out)
{
    int ret = open_lib();
    if (ret < 0)
        return ret;

    ret = lib_sensors_module->common.methods->
        open((hw_module_t *) lib_sensors_module, name, &lib_hw_device);
    if (ret < 0) {
        dlclose(lib_handle);
        return ret;
    }

    memset(&dev, 0, sizeof(sensors_poll_device_1_t));
    dev.common.tag     = HARDWARE_DEVICE_TAG;
    dev.common.version = SENSORS_DEVICE_API_VERSION_1_3;
    dev.common.module  = const_cast<hw_module_t*>(hw_module);
    dev.common.close   = sensor_device_close;
    dev.activate       = sensor_device_activate;
    dev.setDelay       = sensor_device_set_delay;
    dev.poll           = sensor_device_poll;
    dev.batch          = sensor_device_batch;
    dev.flush          = sensor_device_flush;

    *hw_device_out = &dev.common;

    return 0;
}

static struct hw_module_methods_t sensors_module_methods = {
    .open = open_sensors
};

struct sensors_module_t HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .module_api_version = SENSORS_MODULE_API_VERSION_0_1,
        .hal_api_version = SENSORS_MODULE_API_VERSION_0_1,
        .id = SENSORS_HARDWARE_MODULE_ID,
        .name = "Flo Sensors Module",
        .author = "Google, Inc",
        .methods = &sensors_module_methods,
        .dso = NULL,
        .reserved = {0},
    },
    .get_sensors_list = sensors_get_sensors_list
};
