LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := RemoveDialer
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE_CLASS := APPS
LOCAL_OVERRIDES_PACKAGES := Dialer GoogleDialer Messages GoogleMessages Messaging
LOCAL_UNINSTALLABLE_MODULE := true
LOCAL_SRC_FILES := /dev/null
LOCAL_CERTIFICATE := PRESIGNED
include $(BUILD_PREBUILT)
