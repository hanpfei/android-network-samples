//
// Created by hanpfei0306 on 17-7-2.
//

#include <stdlib.h>

#include "jni.h"

#include "JNIHelper.h"

#define TAG "hellojni"

static jstring JniTest_stringFromJNI(JNIEnv* env, jobject thiz) {
    const char *str = "JNI_OnLoad - Hello from JNI !";
    return env->NewStringUTF(str);
}

static void JniTest_setStringToJNI(JNIEnv* env, jobject thiz, jstring jstr) {
    const char *str = env->GetStringUTFChars(jstr, NULL);
    LOGI("%s", str);
    env->ReleaseStringUTFChars(jstr, str);
}

static JNINativeMethod gJniTestMethods[] = {
        NATIVE_METHOD(JniTest, stringFromJNI, "()Ljava/lang/String;"),
        NATIVE_METHOD(JniTest, setStringToJNI, "(Ljava/lang/String;)V"),
};

static int jniRegisterNativeMethods(JNIEnv *env, const char *classPathName,
                                    JNINativeMethod *nativeMethods,
                                    jint nMethods) {
    jclass clazz;
    clazz = env->FindClass(classPathName);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, nativeMethods, nMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

static void register_com_wolfcstech_hellojni_JniTest(JNIEnv *env) {
    jniRegisterNativeMethods(env, "com/wolfcstech/hellojni/JniTest",
                             gJniTestMethods, NELEM(gJniTestMethods));
}

// DalvikVM calls this on startup, so we can statically register all our native methods.
jint JNI_OnLoad(JavaVM *vm, void *) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        LOGE("JavaVM::GetEnv() failed");
        abort();
    }

    register_com_wolfcstech_hellojni_JniTest(env);

    return JNI_VERSION_1_6;
}