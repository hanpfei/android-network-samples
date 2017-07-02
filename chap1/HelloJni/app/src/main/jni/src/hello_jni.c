#include <android/log.h>

#include <stdio.h>

#include "jni.h"

#include "com_wolfcstech_hellojni_JniTest.h"

#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define LOG_TAG "hellojni"

JNIEXPORT jstring
JNICALL Java_com_wolfcstech_hellojni_JniTest_stringFromJNI(JNIEnv* env, jobject thiz) {
    const char *str = "Hello from JNI !";
    return (*env)->NewStringUTF(env, str);
}

JNIEXPORT void
JNICALL Java_com_wolfcstech_hellojni_JniTest_setStringToJNI(JNIEnv* env,
        jobject thiz, jstring jstr) {
    const char *str = (*env)->GetStringUTFChars(env, jstr, NULL);
    LOGI("%s", str);
    (*env)->ReleaseStringUTFChars(env, jstr, str);
}
