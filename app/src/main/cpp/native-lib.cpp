#include <jni.h>
#include "include/util/Debug.h"
#include "Render.h"

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

Render *_render;

JNIEXPORT void JNICALL
Java_com_tcl_opengles_jni_JNI_createEsJNI(JNIEnv *env, jobject /* this */, jobject assetManager) {
    LOGD("~~~createEsJNI()~~~\n");
    _render = new Render();
    _render->createEs(env, assetManager);
}

JNIEXPORT void JNICALL
Java_com_tcl_opengles_jni_JNI_changeEsJNI(JNIEnv *env, jobject /* this */, jint width, jint height) {
    LOGD("~~~changeEsJNI()~~~\n");
    _render->changeEs(width, height);
}

JNIEXPORT void JNICALL
Java_com_tcl_opengles_jni_JNI_drawEsJNI(JNIEnv *env, jobject /* this */) {
    LOGD("~~~drawEsJNI()~~~\n");
    _render->drawEs();
}

JNIEXPORT void JNICALL
Java_com_tcl_opengles_jni_JNI_destoryEsJNI(JNIEnv *env, jobject /* this */) {
    LOGD("~~~destoryEsJNI()~~~\n");
    _render->~Render();
}

#ifdef __cplusplus
}
#endif//__cplusplus
