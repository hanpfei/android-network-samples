LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_CFLAGS := -fvisibility=hidden -DDEBUG
LOCAL_MODULE    := android-ndk-profiler

LOCAL_C_INCLUDES := $(LOCAL_PATH)/3rd/android-ndk-profiler/
LOCAL_SRC_FILES := $(LOCAL_PATH)/3rd/android-ndk-profiler/gnu_mcount.S \
    $(LOCAL_PATH)/3rd/android-ndk-profiler/prof.c \
    $(LOCAL_PATH)/3rd/android-ndk-profiler/read_maps.c
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(LOCAL_PATH)/src/hello_jni.cpp

LOCAL_CFLAGS := -Wno-sign-compare -Wno-error

LOCAL_CFLAGS += -pg

LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd/android-ndk-profiler/ \
    $(LOCAL_PATH)/src/

LOCAL_STATIC_LIBRARIES := android-ndk-profiler

LOCAL_LDLIBS += -llog

LOCAL_MODULE := hellojni

LOCAL_MODULE_TAGS := debug

include $(BUILD_SHARED_LIBRARY)