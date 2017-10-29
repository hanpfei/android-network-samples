//
// Created by hanpfei0306 on 17-7-2.
//

#include <stdlib.h>
#include <unistd.h>

#include "jni.h"

#include "JNIHelper.h"
#include "MemoryTrace.hpp"

#define TAG "hellojni"

static jstring JniTest_stringFromJNI(JNIEnv* env, jobject thiz) {
    const char *str = "JNI_OnLoad - Hello from JNI !";
    return env->NewStringUTF(str);
}

static void JniTest_setStringToJNI(JNIEnv* env, jobject thiz, jstring jstr) {
    const char *str = env->GetStringUTFChars(jstr, NULL);
    if (str == NULL) {
        return; // OutOfMemoryError already thrown
    }
    LOGI("%s", str);
    env->ReleaseStringUTFChars(jstr, str);
}

static jint JniTest_sumIntWithNative(JNIEnv* env, jobject thiz,
        jintArray dataElement, jint start, jint end ) {
    LOGI("from HelloJni_sumIntWithNative");
    jint sum = 0;
    jint*dateArray = env->GetIntArrayElements(dataElement, NULL);
    for (int i = start; i < end; ++ i) {
        sum += dateArray[i];
    }
    env->ReleaseIntArrayElements(dataElement, dateArray, 0);
    return sum;
}

static jdouble JniTest_sumDoubleWithNative(JNIEnv* env, jobject thiz,
        jdoubleArray dataElement, jint start, jint end) {
    LOGI("from HelloJni_sumDoubleWithNative");
    jdouble sum = 0.0;
    jdouble *dataArray = env->GetDoubleArrayElements(dataElement, NULL);
    for (int i = start; i < end; ++ i) {
        sum += dataArray[i];
    }
    env->ReleaseDoubleArrayElements(dataElement, dataArray, 0);
    return sum;
}

static jobjectArray JniTest_initInt2DArray(JNIEnv* env, jobject thiz, jint size) {
    jobjectArray result;
    int i;
    jclass intArrCls = env->FindClass("[I");
    if (intArrCls == NULL) {
        return NULL; /* exception thrown */
    }
    result = env->NewObjectArray(size, intArrCls, NULL);
    if (result == NULL) {
        return NULL; /* out of memory error thrown */
    }
    for (i = 0; i < size; i++) {
        jint tmp[256]; /* make sure it is large enough! */
        int j;
        jintArray iarr = env->NewIntArray(size);
        if (iarr == NULL) {
            return NULL; /* out of memory error thrown */
        }
        for (j = 0; j < size; j++) {
            tmp[j] = i + j;
        }
        env->SetIntArrayRegion(iarr, 0, size, tmp);
        env->SetObjectArrayElement(result, i, iarr);
        env->DeleteLocalRef(iarr);
    }
    return result;
}

static void JniTest_accessField(JNIEnv* env, jobject thiz) {
    jfieldID fid; /* Store the field ID */
    jstring jstr;
    const char *str;

    /* Get a reference to obj's class */
    jclass cls = env->FindClass("com/wolfcstech/hellojni/JniTest");

    /* Look for the instance field str in cls */
    fid = env->GetFieldID(cls, "str", "Ljava/lang/String;");
    if (fid == NULL) {
        return; /* Failed to find the field */
    }

    /* Read the instance field str */
    jstr = (jstring)env->GetObjectField(thiz, fid);
    str = env->GetStringUTFChars(jstr, NULL);
    if (str == NULL) {
        return; /* Out of memory */
    }
    LOGI(" instancField.str = \" %s \"", str);
    env->ReleaseStringUTFChars(jstr, str);

    /* Create a new string and overwrite the instance field */
    jstr = env->NewStringUTF("123");
    if (jstr == NULL) {
        return; /* Out of memory */
    }
    env->SetObjectField(thiz, fid, jstr);
}

static void JniTest_accessStaticField(JNIEnv* env, jobject thiz) {
    jfieldID fid; /* Store the field ID */
    jint si;

    /* Get a reference to obj's class */
    jclass cls = env->GetObjectClass(thiz);

    /* Look for the instance field str in cls */
    fid = env->GetStaticFieldID(cls, "staticInt", "I");
    if (fid == NULL) {
        return; /* Failed to find the field */
    }
    /* Access the static field staticInt */
    si = env->GetStaticIntField(cls, fid);
    LOGI(" FieldAccess.staticInt = %d", si);
    env->SetStaticIntField(cls, fid, 200);
}

static void JniTest_accessStaticFieldInStaticNativeMethod(JNIEnv* env, jclass jcls) {
    jfieldID fid; /* Store the field ID */
    jint si;

    /* Get a reference to obj's class */
    jclass cls = jcls;

    /* Look for the instance field str in cls */
    fid = env->GetStaticFieldID(cls, "staticInt", "I");
    if (fid == NULL) {
        return; /* Failed to find the field */
    }
    /* Access the static field staticInt */
    si = env->GetStaticIntField(cls, fid);
    LOGI(" FieldAccess.staticInt = %d in accessStaticFieldInStaticNativeMethod", si);

    leaktracer::MemoryTrace::GetInstance().stopAllMonitoring();

    sleep(3);
    LOGI("To writeLeaksToFile %s.", "/sdcard/leaks.out");
    leaktracer::MemoryTrace::GetInstance().writeLeaksToFile("/sdcard/leaks.out");
}

static void JniTest_nativeCallMethod(JNIEnv* env, jobject thiz) {
    jclass cls = env->GetObjectClass(thiz);
    jmethodID mid = env->GetMethodID(cls, "callback", "()V");
    if (mid == NULL) {
        return;
    }
    LOGI("In native code");
    env->CallVoidMethod(thiz, mid);
}

static void JniTest_nativeCallStaticMethod(JNIEnv* env, jobject thiz) {
    jclass cls = env->GetObjectClass(thiz);
    jmethodID mid = env->GetStaticMethodID(cls, "callbackStatic", "()V");
    if (mid == NULL) {
        return;
    }
    LOGI("In native code static");
    env->CallStaticVoidMethod(cls, mid);
}

static JNINativeMethod gJniTestMethods[] = {
        NATIVE_METHOD(JniTest, stringFromJNI, "()Ljava/lang/String;"),
        NATIVE_METHOD(JniTest, setStringToJNI, "(Ljava/lang/String;)V"),
        NATIVE_METHOD(JniTest, sumIntWithNative, "([III)I"),
        NATIVE_METHOD(JniTest, sumDoubleWithNative, "([DII)D"),
        NATIVE_METHOD(JniTest, initInt2DArray, "(I)[[I"),
        NATIVE_METHOD(JniTest, accessField, "()V"),
        NATIVE_METHOD(JniTest, accessStaticField, "()V"),
        NATIVE_METHOD(JniTest, accessStaticFieldInStaticNativeMethod, "()V"),
        NATIVE_METHOD(JniTest, nativeCallMethod, "()V"),
        NATIVE_METHOD(JniTest, nativeCallStaticMethod, "()V")
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

char *doAlloc(unsigned int size);

static void register_com_wolfcstech_hellojni_JniTest(JNIEnv *env) {
    jniRegisterNativeMethods(env, "com/wolfcstech/hellojni/JniTest",
                             gJniTestMethods, NELEM(gJniTestMethods));

    // startup part of the program
    // following allocation is not registered
    char *lostAtStartup = doAlloc(128); strcpy(lostAtStartup, "Lost at startup");

    // starting monitoring allocations
    leaktracer::MemoryTrace::GetInstance().startMonitoringAllThreads();
    char *memLeak = doAlloc(256); strcpy(memLeak, "This is a real memory leak");
    char *notLeak = doAlloc(64); strcpy(notLeak, "This is NOT a memory leak");

    char *memLeak2 = (char*)malloc(256); strcpy(memLeak2, "This is a malloc memory leak");
    free(lostAtStartup);


    // stop monitoring allocations, but do still
    // monitor releases of the memory
    leaktracer::MemoryTrace::GetInstance().stopMonitoringAllocations();
    delete[] notLeak;
    notLeak = doAlloc(32);

    // stop all monitoring, print report
    leaktracer::MemoryTrace::GetInstance().stopAllMonitoring();

    leaktracer::MemoryTrace::GetInstance().writeLeaksToFile("/sdcard/leaks.out");
}

char *doAlloc(unsigned int size) {
	return new char[size];
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