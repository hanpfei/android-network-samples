package com.wolfcstech.hellojni;

import android.util.Log;

public class JniTest {
    private static final String TAG = "JniTest";

    public native String stringFromJNI();

    public native void setStringToJNI(String str);

    public native String unimplementedStringFromJNI();

    public native int sumIntWithNative(int[] dataElement, int start, int end);

    public native double sumDoubleWithNative (double[] dataElement, int start, int end);

    public native int[][] initInt2DArray(int size);

    private String str = "";
    private static int staticInt;

    public native void accessField();
    public void setString(String text) {
        str = text;
    }
    public String getString() {
        return str;
    }

    public native void accessStaticField();
    public void setStaticInt(int intValue) {
        staticInt = intValue;
    }
    public int getStaticInt() {
        return staticInt;
    }

    public static native void accessStaticFieldInStaticNativeMethod();

    public native void nativeCallMethod();
    private void callback() {
        Log.d(TAG, "In java");
    }

    public native void nativeCallStaticMethod();

    private static void callbackStatic() {
        Log.d(TAG, "In java staic");
    }

    static {
        System.loadLibrary("hellojni");
    }
}
