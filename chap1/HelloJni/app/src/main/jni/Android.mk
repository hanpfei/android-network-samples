LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := $(LOCAL_PATH)/src/hello_jni.c

LOCAL_CFLAGS := -Wno-sign-compare -Wno-error

LOCAL_C_INCLUDES +=

LOCAL_LDLIBS += -llog

LOCAL_MODULE := hellojni

LOCAL_MODULE_TAGS := debug

include $(BUILD_SHARED_LIBRARY)


