package com.wolfcstech.hellojni;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.tv);
        JniTest jniTest = new JniTest();
        tv.setText(jniTest.stringFromJNI());

        jniTest.setStringToJNI("String from java");

        int[] dataElement = new int[] {
                2, 3, 4, 6
        };
        int sum = jniTest.sumIntWithNative(dataElement, 0, dataElement.length);
        Log.d(TAG, "sum = " + sum);

        double[] doubleElement = new double[] {
                3.4, 5.3, 7.6, 9.2
        };
        double doubleSum = jniTest.sumDoubleWithNative(doubleElement, 0, doubleElement.length);
        Log.d(TAG, "doubleSum = " + doubleSum);

        int[][] i2arr = jniTest.initInt2DArray(3);
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                Log.d(TAG, " " + i2arr[i][j]);
            }
        }

        jniTest.setString("abc");
        jniTest.accessField();
        Log.d(TAG, "In java: " + " instancField.str = \"" + jniTest.getString() + "\"");

        jniTest.setStaticInt(100);
        jniTest.accessStaticField();
        Log.d(TAG, "In java: " + " FieldAccess.staticInt = " + jniTest.getStaticInt());

        jniTest.accessStaticFieldInStaticNativeMethod();

        jniTest.nativeCallMethod();
        jniTest.nativeCallStaticMethod();
    }
}
