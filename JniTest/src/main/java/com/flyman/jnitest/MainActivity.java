package com.flyman.jnitest;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import com.flyman.jnitest.bridge.TestJniBridge;

public class MainActivity extends AppCompatActivity {
    private TestJniBridge testJniBridge;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        testJniBridge = new TestJniBridge();
        TestJniBridge.test();
    }
}
