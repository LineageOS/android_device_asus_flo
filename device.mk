#
# Copyright (C) 2011 The Android Open-Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

PRODUCT_PROPERTY_OVERRIDES := \
    ro.carrier=wifi-only

# Camera
PRODUCT_PACKAGES += \
    camera.flo

# the actual meat of the device-specific product definition
$(call inherit-product, $(LOCAL_PATH)/device-common.mk)

# Overlays
DEVICE_PACKAGE_OVERLAYS += \
    $(LOCAL_PATH)/overlay \
    $(LOCAL_PATH)/overlay-lineage

PRODUCT_ENFORCE_RRO_TARGETS := \
    framework-res
    
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/rootdir/etc/fstab.flo:$(TARGET_COPY_OUT_RAMDISK)/fstab.flo \
    $(LOCAL_PATH)/rootdir/etc/fstab.flo:$(TARGET_COPY_OUT_VENDOR)/etc/fstab.flo
