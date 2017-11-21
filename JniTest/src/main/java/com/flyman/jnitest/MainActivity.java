package com.flyman.jnitest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

import com.flyman.jnitest.bridge.TestJniBridge;

import butterknife.BindView;
import butterknife.ButterKnife;
import butterknife.OnClick;

public class MainActivity extends AppCompatActivity {
    @BindView(R.id.btn_create_pthread)
    Button btnCreatePthread;
    private TestJniBridge testJniBridge;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ButterKnife.bind(this);
        testJniBridge = new TestJniBridge();
        TestJniBridge.test();
        byte[] bytes = new byte[]{10, 11};
        testJniBridge.testByteArray(bytes, bytes.length);
    }

    @OnClick({R.id.btn_create_pthread})
    public void onViewClicked(View view) {
        switch (view.getId()){
            case R.id.btn_create_pthread:
                testJniBridge.testRunPthread("m==========xxxxxssggt");
                break;
        }

    }
}
