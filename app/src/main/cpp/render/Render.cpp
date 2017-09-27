//
// Created by 7088"ES" on 2017/"ES"/22.
//

#include <GLES/gl.h>
#include "Render.h"
#include "../util/Debug.h"

#ifdef __cplusplus
extern "C" {
#endif

Render::Render() {

}

Render::~Render() {

}

void Render::init() {
    LOGD("~~~init()~~~");
}

void Render::createEs(JNIEnv *env, jobject assetManager) {
    LOGD("~~~createEs()~~~");
    init();
    glClearColor(0.0,0.0,0.0,0.0);
}

void Render::changeEs(int width, int height) {
    LOGD("~~~changeEs()~~~");
    glViewport(0,0,width,height);
}

void Render::drawEs() {
    LOGD("~~~drawEs()~~~");
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

}


#ifdef __cplusplus
}
#endif