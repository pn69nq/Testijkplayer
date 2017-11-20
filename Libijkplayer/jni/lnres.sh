#!/bin/bash
PRODUCT_DIR=/mnt/jjfly_d/gitlab/ijkplayer-android
PRODUCT_LIB=/mnt/jjfly_d/gitlab/ijkplayer-android/android/ijkplayer/Libijkplayer/
ln -s $PRODUCT_DIR/ijkprof/android-ndk-profiler-dummy/jni $PRODUCT_LIB/src/main/jni/android-ndk-prof
ln -s $PRODUCT_DIR/ijkmedia $PRODUCT_LIB/src/main/jni/ijkmedia