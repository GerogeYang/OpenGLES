#include <jni.h>
#include "render/Render.h"
#include "util/Debug.h"

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

Render _render;

JNIEXPORT void JNICALL
Java_com_tcl_opengles_jni_JNI_createEsJNI(JNIEnv *env, jobject /* this */, jobject assetManager) {
    LOGD("~~~createEsJNI()~~~");
    _render.createEs(env, assetManager);
}

JNIEXPORT void JNICALL
Java_com_tcl_opengles_jni_JNI_changeEsJNI(JNIEnv *env, jobject /* this */, jint width, jint height) {
    LOGD("~~~changeEsJNI()~~~");
    _render.changeEs(width, height);
}

JNIEXPORT void JNICALL
Java_com_tcl_opengles_jni_JNI_drawEsJNI(JNIEnv *env, jobject /* this */) {
    LOGD("~~~drawEsJNI()~~~");
    _render.drawEs();
}

JNIEXPORT void JNICALL
Java_com_tcl_opengles_jni_JNI_destoryEsJNI(JNIEnv *env, jobject /* this */) {
    LOGD("~~~destoryEsJNI()~~~");
    _render.~Render();
}

#ifdef __cplusplus
}
#endif//__cplusplus
