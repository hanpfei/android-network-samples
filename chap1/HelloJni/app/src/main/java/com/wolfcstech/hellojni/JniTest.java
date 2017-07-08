package com.wolfcstech.hellojni;

public class JniTest {
    public native String stringFromJNI();

    public native void setStringToJNI(String str);

    public native String unimplementedStringFromJNI();

    public native int sumIntWithNative(int[] dataElement, int start, int end);

    public native double sumDoubleWithNative (double[] dataElement, int start, int end);

    public native int[][] initInt2DArray(int size);

    static {
        System.loadLibrary("hellojni");
    }
}
