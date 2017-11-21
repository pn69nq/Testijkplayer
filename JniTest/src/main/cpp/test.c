#include "test.h"
#include <jni.h>
#include "thread/test_pthread.h"
#include "util/JniConverHelper.h"
#include "util/Log.h"

#define JNI_CLASS_TEST     "com/flyman/jnitest/bridge/TestJniBridge"
#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

void jniTest(JNIEnv *env, jclass thiz)
{
    LOGD("test =77777===================================");
}

void jniTestRunPthread(JNIEnv *env, jobject obj,jstring jstr)
{
    runThread(jstring2chars(env,jstr));
}

void jnitestByteArray(JNIEnv *env, jobject obj,jbyteArray array,jint size)
{
    unsigned char * buffer = jbyteArray2byteArray(env,array);
//    LOGD("test 12=====%d %x",buffer[0],buffer[0]);
//    LOGD("test 12=====%d %x",buffer[1],buffer[1]);
    int len = 0;
    GET_ARRAY_LEN(buffer,len)
    LOGD("test 12=====%d",len);


}

static JNINativeMethod g_methods[] = {
        { "test",       "()V",     (void *) jniTest },
        {"testRunPthread","(Ljava/lang/String;)V",(void *)jniTestRunPthread},
        {"testByteArray","([BI)V",(void *)jnitestByteArray}
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