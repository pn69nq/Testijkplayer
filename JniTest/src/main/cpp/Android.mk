LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := testjni
LOCAL_C_INCLUDES := $(LOCAL_PATH)/util
LOCAL_LDLIBS := -llog
LOCAL_SRC_FILES := \
    test.c \
    thread/test_pthread.c \
    thread/threadpool.c \
    util/JniConverHelper.c



include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH := $(call my-dir)