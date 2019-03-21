#!/usr/bin/env bash

NDK_PROJECT_PATH=./

function build_so(){
    DEBUG=1
    RELEASE=0
    ANDROID_MK=Android.mk
    APPLICATION_MK=Application.mk
    /mnt/soft/android/android-ndk-r10e/ndk-build NDK_PROJECT_PATH=$NDK_PROJECT_PATH -j8 \
 APP_BUILD_SCRIPT=$ANDROID_MK \
 NDK_APPLICATION_MK=$APPLICATION_MK \
 NDK_DEBUG=$RELEASE
}

function clean(){
    /mnt/soft/android/android-ndk-r10e/ndk-build clean
}
#set_env
build_so