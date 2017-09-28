//
// Created by 7088"ES" on 2017/"ES"/22.
//

#include <GLES2/gl2.h>
#include <GLES/gl.h>
#include "Render.h"
#include "../util/Debug.h"

#ifdef __cplusplus
extern "C" {
#endif

GLfloat gVertexts[] ={
        0.0f,1.0f,-3.0f,
        1.0f,0.0f,-3.0f,
        -1.0f,0.0f,-3.0f
};

Render::Render() {

}

Render::~Render() {

}

void Render::init() {
    LOGD("~~~init()~~~");
}

void Render::createEs(JNIEnv *env, jobject assetManager) {
    LOGD("~~~createEs()~~~");
}

void Render::changeEs(int width, int height) {
    LOGD("~~~changeEs()~~~");
    glViewport(0,0,width,height);
}

void Render::drawEs() {
    LOGD("~~~drawEs()~~~");
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0, 0.0, 0.0, 0.0); //设置屏幕背景色RGBA
}


#ifdef __cplusplus
}
#endif