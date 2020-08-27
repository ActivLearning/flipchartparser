#include "commonlog.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <iostream>

void logDebugStr(const char* file, int line, const char* format, ...) {


    va_list vl;
    char buf[1000000]{0};
    va_start(vl, format);
    vsprintf(buf, format, vl);
    va_end(vl);

    std::cout << "[" << file << "]" << "(" << line << ")"<< buf << std::endl;

#ifdef ANDROID
    ANDROID_LOG(format, buf);
#endif
}
