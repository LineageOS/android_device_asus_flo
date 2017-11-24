#!/bin/bash
#
# Copyright (C) 2016 The CyanogenMod Project
# Copyright (C) 2017 The LineageOS Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -e

VENDOR=asus
DEVICE_COMMON=flo
DEVICE=${DEVICE:-flo}
export INITIAL_COPYRIGHT_YEAR=2013

# Load extractutils and do some sanity checks
MY_DIR="${BASH_SOURCE%/*}"
if [[ ! -d "$MY_DIR" ]]; then MY_DIR="$PWD"; fi

CM_ROOT="$MY_DIR"/../../..

HELPER="$CM_ROOT"/vendor/lineage/build/tools/extract_utils.sh
if [ ! -f "$HELPER" ]; then
    echo "Unable to find helper script at $HELPER"
    exit 1
fi
. "$HELPER"

# Initialize the helper
setup_vendor "$DEVICE_COMMON" "$VENDOR" "$CM_ROOT" true

# Copyright headers and guards
write_headers "flo deb"

# The standard blobs
write_makefiles "$MY_DIR"/proprietary-blobs.txt

# Done
write_footers

if [ "$DEVICE" '!=' "$DEVICE_COMMON" ]; then
	# Reinitialize the helper for the device-specific blobs
	setup_vendor "$DEVICE" "$VENDOR" "$CM_ROOT"

	# Copyright headers and guards
	write_headers

	# The device-specific blobs
	write_makefiles "$MY_DIR"/../$DEVICE/proprietary-blobs.txt

	# Done
	write_footers
fi


