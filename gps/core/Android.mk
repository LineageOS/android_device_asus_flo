LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libloc_core
LOCAL_MODULE_OWNER := qcom
LOCAL_PROPRIETARY_MODULE := true

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
    libutils \
    liblog \
    libcutils \
    libgps.utils \
    libdl \
    libprocessgroup

LOCAL_SRC_FILES += \
    MsgTask.cpp \
    LocApiBase.cpp \
    LocAdapterBase.cpp \
    ContextBase.cpp \
    LocDualContext.cpp \
    loc_core_log.cpp

LOCAL_CFLAGS += \
     -fno-short-enums \
     -D_ANDROID_ \
     -Wno-unused-parameter \
     -Wno-error \

LOCAL_C_INCLUDES:= \
    $(TARGET_OUT_HEADERS)/gps.utils

LOCAL_COPY_HEADERS_TO:= libloc_core/
LOCAL_COPY_HEADERS:= \
    MsgTask.h \
    LocApiBase.h \
    LocAdapterBase.h \
    ContextBase.h \
    LocDualContext.h \
    IzatProxyBase.h \
    UlpProxyBase.h \
    gps_extended_c.h \
    gps_extended.h \
    loc_core_log.h

include $(BUILD_SHARED_LIBRARY)
