//
// Created by jjfly on 17-11-19.
//

#include "test.h"
#include <jni.h>
#include <android/log.h>

#define JNI_CLASS_TEST     "com/flyman/jnitest/bridge/TestJniBridge"
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

void jniTest(JNIEnv *env, jclass thiz){
    LOGD("test =77777===================================");
}

static JNINativeMethod g_methods[] = {
        { "test",       "()V",     (void *) jniTest }
};



JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JNIEnv* env = NULL;
    jclass clazz = NULL;
    if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_4) != JNI_OK){
        return -1;
    }
    // FindClass returns LocalReference
    clazz = (*env)->FindClass(env, JNI_CLASS_TEST); \
    (*env)->RegisterNatives(env, clazz, g_methods, NELEM(g_methods) );

    return JNI_VERSION_1_4;
}


JNIEXPORT void JNI_OnUnload(JavaVM *jvm, void *reserved)
{

}