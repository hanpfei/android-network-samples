LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(LOCAL_PATH)/src/hello_jni.cpp

LOCAL_SRC_FILES += $(LOCAL_PATH)/3rd/libleaktracer/src/AllocationHandlers.cpp \
    $(LOCAL_PATH)/3rd/libleaktracer/src/MemoryTrace.cpp

LOCAL_CFLAGS := -Wno-sign-compare -Wno-error

LOCAL_C_INCLUDES += $(LOCAL_PATH)/3rd/libleaktracer/include/

LOCAL_LDLIBS += -llog

LOCAL_MODULE := hellojni

LOCAL_MODULE_TAGS := debug

include $(BUILD_SHARED_LIBRARY)