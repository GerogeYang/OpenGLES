//
// Created by 7088"ES" on 2017/"ES"/22.
//

#include <GLES2/gl2.h>
#include "Render.h"

#ifdef __cplusplus
extern "C" {
#endif

Render::Render() {

}

Render::~Render() {

}

void Render::init() {

}

void Render::createEs(JNIEnv *env, jobject assetManager) {
    init();
    glClearColor(0.0,0.0,0.0,0.0);
}

void Render::changeEs(int width, int height) {

}

void Render::drawEs() {
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}


#ifdef __cplusplus
}
#endif