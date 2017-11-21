#ifndef PROJ_ANDROID_STUDIO_JNICONVERHELPER_H
#define PROJ_ANDROID_STUDIO_JNICONVERHELPER_H
#include <jni.h>
#include "util/Log.h"
#include <string.h>
#define GET_ARRAY_LEN(array,len) {len = (sizeof(array) / sizeof(array[0]));}

/***
 *     java 转 c++
 *     不需要转换
 *     jboolean;jint;jlong jfloat
 *
 *
 */

const char* jstring2chars(JNIEnv *env,jstring jstr);
//char 转jstring
jstring chars2jstring(JNIEnv *env,char *chars);

//jbyteArray 转 char数组
unsigned char* jbyteArray2byteArray(JNIEnv *env,jbyteArray datas);

//char array 转 jbyteArray
jbyteArray byteArray2JbyteArray(JNIEnv *env, unsigned char * charAry);


#endif
