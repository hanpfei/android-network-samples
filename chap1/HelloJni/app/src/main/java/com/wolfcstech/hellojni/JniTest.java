package com.wolfcstech.hellojni;

public class JniTest {
    public native String stringFromJNI();

    public native void setStringToJNI(String str);

    public native String unimplementedStringFromJNI();

    static {
        System.loadLibrary("hellojni");
    }
}
