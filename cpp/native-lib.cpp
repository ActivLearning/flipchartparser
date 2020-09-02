//
// Created by admin on 2019-08-19.
//


#include <jni.h>
#include <string>

#include "src/util/commonlog.h"
#include "src/FlipChartController.h"



#define JAVA(X) JNIEXPORT Java_com_nd_flipchartparser_FlipchartparserPlugin_##X

FlipChartController* pController ;


extern  "C"
{
    jstring JAVA(openFlipchart)(JNIEnv *env, jobject obj,
            jstring flipChartPath,
            jstring uncompressPath)
    {
        jboolean isCopy;
        const char* srcPath = env->GetStringUTFChars(flipChartPath, &isCopy);
        const char* uPath = env->GetStringUTFChars(uncompressPath, &isCopy);

        if(pController != nullptr)
        {
            delete pController;
            pController = nullptr;
            
        }
        pController = new FlipChartController();
        std::string result = pController->openFlipchart(srcPath, uPath);
        env->ReleaseStringUTFChars(flipChartPath,srcPath);
        env->ReleaseStringUTFChars(uncompressPath,uPath);
        return env->NewStringUTF(result.c_str());
    }

    jstring JAVA(loadPage)(JNIEnv *env, jobject obj,
                           jint pageNumber)
    {
        jint val = 100;
        LOGDEBUG("pageNumber-->%d", val);

        std::string result = "";

        if(pController != NULL)
        {
            result = pController->loadPage(pageNumber);
        }
        return env->NewStringUTF(result.c_str());
    }

}