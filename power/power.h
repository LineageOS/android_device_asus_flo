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
    int boost;
    int boostpulse_duration;
    int go_hispeed_load;
    int go_hispeed_load_off;
    int hispeed_freq;
    int hispeed_freq_off;
    int io_is_busy;
    int min_sample_time;
    int max_freq_hysteresis;
    char *target_loads;
    char *target_loads_off;
    int scaling_max_freq;
} power_profile;

static power_profile profiles[PROFILE_MAX] = {
    [PROFILE_POWER_SAVE] = {
        .boost = 0,
        .boostpulse_duration = 0,
        .go_hispeed_load = 90,
        .go_hispeed_load_off = 90,
        .hispeed_freq = 702000,
        .hispeed_freq_off = 702000,
        .io_is_busy = 0,
        .min_sample_time = 60000,
        .max_freq_hysteresis = 100000,
        .target_loads = "95 1728000:99",
        .target_loads_off = "95 1512000:99",
        .scaling_max_freq = 702000,
    },
    [PROFILE_BALANCED] = {
        .boost = 0,
        .boostpulse_duration = 60000,
        .go_hispeed_load = 80,
        .go_hispeed_load_off = 90,
        .hispeed_freq = 918000,
        .hispeed_freq_off = 702000,
        .io_is_busy = 1,
        .min_sample_time = 60000,
        .max_freq_hysteresis = 100000,
        .target_loads = "80 918000:90 1512000:99",
        .target_loads_off = "95 1512000:99",
        .scaling_max_freq = 1512000,
    },
    [PROFILE_HIGH_PERFORMANCE] = {
        .boost = 1,
        .boostpulse_duration = 0, /* prevent unnecessary write */
        .go_hispeed_load = 50,
        .go_hispeed_load_off = 50,
        .hispeed_freq = 918000,
        .hispeed_freq_off = 918000,
        .io_is_busy = 1,
        .min_sample_time = 60000,
        .max_freq_hysteresis = 100000,
        .target_loads = "80",
        .target_loads_off = "80",
        .scaling_max_freq = 1512000
    },
    [PROFILE_BIAS_POWER_SAVE] = {
        .boost = 0,
        .boostpulse_duration = 0,
        .go_hispeed_load = 90,
        .go_hispeed_load_off = 90,
        .hispeed_freq = 787200,
        .hispeed_freq_off = 787200,
        .io_is_busy = 0,
        .min_sample_time = 60000,
        .max_freq_hysteresis = 100000,
        .target_loads = "95 1190400:99",
        .target_loads_off = "95 1190400:99",
        .scaling_max_freq = 1190400,
    },
};
