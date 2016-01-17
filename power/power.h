/*
 * Copyright (C) 2015 The CyanogenMod Project
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

enum {
    PROFILE_POWER_SAVE = 0,
    PROFILE_BALANCED,
    PROFILE_HIGH_PERFORMANCE,
    PROFILE_BIAS_POWER_SAVE,
    PROFILE_MAX
};

typedef struct governor_settings {
    int is_interactive;
    int go_hispeed_load;
    int go_hispeed_load_off;
    int hispeed_freq;
    int timer_rate;
    int timer_rate_off;
    int above_hispeed_delay;
    int io_is_busy;
    int min_sample_time;
    int max_freq_hysteresis;
    char *target_loads;
    char *target_loads_off;
    int limited_min_freq;
    int limited_max_freq;
} power_profile;

static power_profile profiles[PROFILE_MAX] = {
    [PROFILE_POWER_SAVE] = {
        .go_hispeed_load = 90,
        .go_hispeed_load_off = 101,
        .hispeed_freq = 702000,
        .timer_rate = 20000,
        .timer_rate_off = 50000,
        .above_hispeed_delay = 39000,
        .io_is_busy = 0,
        .min_sample_time = 40000,
        .max_freq_hysteresis = 80000,
        .target_loads = "95 1512000:99",
        .target_loads_off = "95 1512000:99",
        .limited_min_freq = 384000,
        .limited_max_freq = 1026000,
    },
    [PROFILE_BALANCED] = {
        .go_hispeed_load = 90,
        .go_hispeed_load_off = 101,
        .hispeed_freq = 918000,
        .timer_rate = 20000,
        .timer_rate_off = 50000,
        .above_hispeed_delay = 39000,
        .io_is_busy = 1,
        .min_sample_time = 40000,
        .max_freq_hysteresis = 80000,
        .target_loads = "90 1512000:99",
        .target_loads_off = "95 1512000:99",
        .limited_min_freq = 384000,
        .limited_max_freq = 1512000,
    },
    [PROFILE_HIGH_PERFORMANCE] = {
        .go_hispeed_load = 90,
        .go_hispeed_load_off = 101,
        .hispeed_freq = 918000,
        .timer_rate = 20000,
        .timer_rate_off = 50000,
        .above_hispeed_delay = 39000,
        .io_is_busy = 1,
        .min_sample_time = 40000,
        .max_freq_hysteresis = 80000,
        .target_loads = "80",
        .target_loads_off = "80",
        .limited_min_freq = 918000,
        .limited_max_freq = 1512000,
    },
    [PROFILE_BIAS_POWER_SAVE] = {
        .go_hispeed_load = 90,
        .go_hispeed_load_off = 101,
        .hispeed_freq = 702000,
        .timer_rate = 20000,
        .timer_rate_off = 50000,
        .above_hispeed_delay = 39000,
        .io_is_busy = 0,
        .min_sample_time = 40000,
        .max_freq_hysteresis = 80000,
        .target_loads = "95 1512000:99",
        .target_loads_off = "95 1512000:99",
        .limited_min_freq = 384000,
        .limited_max_freq = 1512000,
    },
};
