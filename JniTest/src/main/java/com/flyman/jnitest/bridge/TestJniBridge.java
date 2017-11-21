package com.flyman.jnitest.bridge;

/**
 * auther:czq
 * date:17-11-19.
 * version:
 * desc:
 */

public class TestJniBridge {

    static {
        System.loadLibrary("testjni");   //defaultConfig.ndk.moduleName
    }

    public static native void test();

    public native void testRunPthread(String name);

    public native void testByteArray(byte[] bytes,int size);

}
