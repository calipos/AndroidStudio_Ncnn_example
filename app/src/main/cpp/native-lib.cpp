#include <jni.h>
#include <android/bitmap.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "ncnnshell.h"

static std::vector<unsigned char> model_param;
static std::vector<unsigned char> model_bin;
extern "C"{


JNIEXPORT jstring JNICALL Java_uner_ii_ncnndemo3_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jstring JNICALL Java_uner_ii_ncnndemo3_MainActivity_debugInit(JNIEnv *env, jobject thiz, jbyteArray param, jbyteArray bin)
{
    {
        int len = env->GetArrayLength(param);
        model_param.resize(len);
        env->GetByteArrayRegion(param, 0, len, (jbyte *) model_param.data());
    }
    {
        int len = env->GetArrayLength(bin);
        model_bin.resize(len);
        env->GetByteArrayRegion(bin, 0, len, (jbyte *) model_bin.data());
    }
    char report[200];
    ncnnShell_DebugInterface(model_param.data(), model_bin.data(),report);
    report[199]='\0';
    return env->NewStringUTF(report);
}


JNIEXPORT jstring JNICALL Java_uner_ii_ncnndemo3_MainActivity_Init(JNIEnv *env, jobject thiz, jbyteArray param, jbyteArray bin)
{
    {
        int len = env->GetArrayLength(param);
        model_param.resize(len);
        env->GetByteArrayRegion(param, 0, len, (jbyte *) model_param.data());
    }
    {
        int len = env->GetArrayLength(bin);
        model_bin.resize(len);
        env->GetByteArrayRegion(bin, 0, len, (jbyte *) model_bin.data());
    }
    char report[200];
    ncnnShell_Init(model_param.data(), model_bin.data(),report);
    report[199]='\0';
    return env->NewStringUTF(report);
}

JNIEXPORT jstring JNICALL Java_uner_ii_ncnndemo3_MainActivity_DetectSSD (JNIEnv *env, jobject thiz, jint h, jint w, jobject bitmap)
{
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bitmap, &info) < 0) {
        return env->NewStringUTF("AndroidBitmap_getInfo err");
    }
    int width = info.width;
    int height = info.height;
    if (width != w || height != h)
        return env->NewStringUTF("w,h not corresponding");
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888)
        return env->NewStringUTF("ANDROID_BITMAP_FORMAT error");
    void *indata;
    if (ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_lockPixels(env, bitmap, &indata)) {
        return env->NewStringUTF("AndroidBitmap_lockPixels error");
    }
    if (ANDROID_BITMAP_RESULT_SUCCESS != AndroidBitmap_unlockPixels(env, bitmap)) {
        return env->NewStringUTF("AndroidBitmap_unlockPixels error");
    }
    char report[200];
    ncnnShell_DetectSSD(h, w, indata, report);
    report[199]='\0';
    return env->NewStringUTF(report);
}


}//extern "c"