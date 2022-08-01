#include <jni.h>
#include <cstring>
#include <android/log.h>
#include <unistd.h>
#include <cstdio>
#include <__threading_support>

#define TAG "UDP-LIB"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);

struct Jni_Context {
    JNIEnv *jniEnv = nullptr;
    jobject instance = nullptr;
};

JavaVM *jvm = nullptr;
bool ifSubThreadRunning = true;

jint JNI_OnLoad(JavaVM *vm, void *args) {
    ::jvm = vm;
    return JNI_VERSION_1_6;
}

void *sub_keep_running_thread(void *args) {

    // step 1 get args
    struct Jni_Context *jniContext = static_cast<Jni_Context *>(args);

    // step 2 get jniEnv
    JNIEnv *subThreadEnv = nullptr;
    jint attachResult = ::jvm->AttachCurrentThread(&subThreadEnv, nullptr);

    if (attachResult != JNI_OK) {
        LOGD("Attach sub thread jni env failed \n");
        return nullptr;
    }

    // step 3 get jclass/jobj
    jobject job = jniContext->instance;
    if (job == nullptr) {
        LOGD("No jobject passed to here \n");
    }

    jclass clazz = subThreadEnv->GetObjectClass(job);

    jmethodID jmId = subThreadEnv->GetMethodID(clazz, "changeText", "(Ljava/lang/String;)V");

    // jfieldID textValFid = subThreadEnv->GetFieldID(clazz, "text2", "Ljava/lang/String;");
    int counter = 0;
    char str[20];

    while (ifSubThreadRunning) {

        sprintf(str, "%d", counter);
        LOGD("%d", counter);
        jstring newVal = subThreadEnv->NewStringUTF(str);
        subThreadEnv->CallVoidMethod(job, jmId, newVal);
        // subThreadEnv->SetObjectField(job, textValFid, newVal);
        counter++;
        sleep(1);
    }

    return nullptr;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_wulala_myapplicationktjni_MainActivity_stringFromJNI(JNIEnv *env, jobject) {
    jstring hw = env->NewStringUTF("Hello from C++");
    return hw;
}

struct Jni_Context jniContext;
pthread_t pid;

extern "C"
JNIEXPORT void JNICALL
Java_com_wulala_myapplicationktjni_MainActivity_changeTextThreadStart(JNIEnv *env, jobject thiz) {

    jniContext.jniEnv = env;  // 这句是没有意义的.
    jniContext.instance = env->NewGlobalRef(thiz);   // 提升为全局引用

    pthread_create(&pid, nullptr, sub_keep_running_thread, (void *) &jniContext);

    // pthread_join(pid, nullptr);
}