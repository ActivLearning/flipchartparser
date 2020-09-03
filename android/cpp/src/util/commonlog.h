#ifndef COMMONLOG_H
#define COMMONLOG_H


#ifdef ANDROID

#include <android/log.h>
extern bool gLogEnabled;
#define  LOG_TAG_NATIVE    "native-lib"

#define ANDROID_LOG(...) __android_log_print(ANDROID_LOG_DEBUG,  LOG_TAG_NATIVE, __VA_ARGS__)

#endif

void logDebugStr(const char* file, int line, const char* format, ...);

#define LOGDEBUG(format, ...) logDebugStr(__FILE__, __LINE__, format, __VA_ARGS__)


#endif // COMMON_H
