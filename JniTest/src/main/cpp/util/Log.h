//
// Created by jjfly on 17-11-20.
//

#ifndef IJKPLAYER_LOG_H
#define IJKPLAYER_LOG_H
#include <android/log.h>

#define  LOG_TAG    "log"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#endif //IJKPLAYER_LOG_H
