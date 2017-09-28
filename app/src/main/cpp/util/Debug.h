//
// Created by 70889 on 2017/9/22.
//

#ifndef OPENGLES_DEBUG_LOG_H
#define OPENGLES_DEBUG_LOG_H

#include <android/log.h>

#define LOG_TAG   OpenGLES-Native-Debug- // 这个是自定义的LOG的标识
#define LOGFUC(arg) #arg  //这个是将宏定义转成字符串
#define LOGFUC1(arg) LOGFUC(arg)
#define LOGFUC2() LOGFUC1(LOG_TAG)

extern bool debugEnable;

// 宏定义类似java 层的定义,不同级别的Log LOGI, LOGD, LOGW, LOGE, LOGF。 对就Java中的 Log.i log.d
//#undef LOG // 取消默认的LOG
#define LOGI(fmt, args...)  if(debugEnable) __android_log_print(ANDROID_LOG_INFO, LOGFUC2(), fmt, ##args)
#define LOGD(fmt, args...)  if(debugEnable) __android_log_print(ANDROID_LOG_DEBUG, LOGFUC2(), fmt, ##args)
#define LOGW(fmt, args...)  if(debugEnable) __android_log_print(ANDROID_LOG_WARN, LOGFUC2(), fmt, ##args)
#define LOGE(fmt, args...)  if(debugEnable) __android_log_print(ANDROID_LOG_ERROR, LOGFUC2(), fmt, ##args)

class Debug {
private:
};

#endif //OPENGLES_DEBUG_LOG_H
