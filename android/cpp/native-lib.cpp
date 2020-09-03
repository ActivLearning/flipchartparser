//
// Created by admin on 2019-08-19.
//


#include <fcntl.h>
#include <jni.h>
#include <string>
#include <unistd.h>

#include "src/util/commonlog.h"
#include "src/FlipChartManager.h"

#define JAVA(X) JNIEXPORT Java_com_nd_flipchartparser_FlipchartparserPlugin_##X
namespace {
    FlipChartManager *m_pFlipchartManager = nullptr;
    const std::string kComponentNoInitial("Flipchart Parser Is Not Initialized");
}

extern "C"
{

jboolean JAVA(config)(JNIEnv *env, jobject obj, jstring tempPath, jboolean logEnabled) {
    jboolean isCopy;
    const char *tempPathCopy = env->GetStringUTFChars(tempPath, &isCopy);
    if (access(tempPathCopy, R_OK | W_OK) == -1) {
        return false;
    }
    if (!m_pFlipchartManager) {
        m_pFlipchartManager = new FlipChartManager;
    }
    m_pFlipchartManager->setTempDir(tempPathCopy);
    return true;
}

jint JAVA(newInstance)(JNIEnv *env, jobject obj) {
    if (!m_pFlipchartManager) {
        return -1;
    }
    return m_pFlipchartManager->newInstance();
}
void JAVA(disposed)(JNIEnv *env, jobject obj, jint handle) {
    if (!m_pFlipchartManager || handle == -1) {
        return;
    }
    m_pFlipchartManager->disposed(handle);
}
jstring JAVA(openFlipchart)(JNIEnv *env, jobject obj, jint handle,
                            jstring flipChartPath) {
    if (!m_pFlipchartManager || handle == -1) {
        return env->NewStringUTF(kComponentNoInitial.data());
    }

    jboolean isCopy;
    const char *srcPath = env->GetStringUTFChars(flipChartPath, &isCopy);
    std::string result = m_pFlipchartManager->loadFlipchart(handle, srcPath);
    env->ReleaseStringUTFChars(flipChartPath, srcPath);

    return env->NewStringUTF(result.c_str());
}

jstring JAVA(loadPage)(JNIEnv *env, jobject obj, jint handle,
                       jint pageNumber) {
    if (!m_pFlipchartManager || handle == -1) {
        return env->NewStringUTF(kComponentNoInitial.data());
    }
    jint val = 100;
    LOGDEBUG("pageNumber-->%d", val);
    std::string result = m_pFlipchartManager->loadPage(handle, pageNumber);
    return env->NewStringUTF(result.c_str());
}

}