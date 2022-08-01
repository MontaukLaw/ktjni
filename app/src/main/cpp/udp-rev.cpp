#include <jni.h>
#include <cstring>
#include <android/log.h>
#include <unistd.h>

#define TAG "UDP-LIB"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);

struct Jni_Context {
    JNIEnv *jniEnv = nullptr;
    jobject instance = nullptr;
};

extern "C" JNIEXPORT jstring JNICALL
Java_com_wulala_myapplicationktjni_MainActivity_stringFromJNI(JNIEnv *env, jobject) {
    jstring hw = env->NewStringUTF("Hello from C++");
    return hw;
}