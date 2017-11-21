#include "JniConverHelper.h"

const char* jstring2chars(JNIEnv *env,jstring jstr)
{
    const char * c_str = (*env)->GetStringUTFChars(env,jstr,NULL);
    size_t len = strlen(c_str);
    LOGD("test=+++==== %s,%d",c_str, len);
    char strAry[len];
    char * str = strAry;
    strcpy(strAry,c_str);
    (*env)->ReleaseStringUTFChars(env,jstr,c_str);
    LOGD("test=+++==== %s",str);
    return (const char *)str;
}

//jstring chars2jstring(JNIEnv *env,char *chars)
//{
//
//}


unsigned char* jbyteArray2byteArray(JNIEnv *env, jbyteArray datas)
{
//    unsigned char* buffer = (unsigned char *)(*env)->GetByteArrayElements(env,datas, 0);
    int len = (*env)->GetArrayLength(env,datas);
    unsigned char byteAry[len];
    (*env)->GetByteArrayRegion(env,datas, 0,len,byteAry);
    int i = 0;
    for(;i<len;i++)
    {
        LOGD("test=======%d %x",byteAry[i],byteAry[i]);
    }
    return byteAry;
}

//jbyteArray byteArray2JbyteArray(JNIEnv *env, unsigned char charAry[])
//{
////    jbyteArray array = (*env)->NewByteArray(env,);
//}