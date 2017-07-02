package com.wolfcstech.hellojni;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.tv);
        JniTest jniTest = new JniTest();
        tv.setText(jniTest.stringFromJNI());

        jniTest.setStringToJNI("String from java");
    }
}
