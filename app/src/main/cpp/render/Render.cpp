//
// Created by 7088"ES" on 2017/"ES"/22.
//

#include <GLES2/gl2.h>
#include <GLES/gl.h>
#include "Render.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"


#ifdef __cplusplus
extern "C" {
#endif


Render::Render():_triangle(NULL) {
    _triangle = new Triangle();
}

Render::~Render() {
    LOGD("~~~~DestoryRender()~~~~~~\n");
    if(NULL != _triangle)
    {
        delete _triangle;
        _triangle = NULL;
    }
}

void Render::printGLString(const char *name, GLenum s)
{
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

void Render::init() {
    LOGD("~~~init()~~~");
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);
    glClearColor(0, 0, 0, 0);
    _triangle->init();
}

void Render::createEs(JNIEnv *env, jobject assetManager) {
    LOGD("~~~createEs()~~~");
    AAssetManager *aamIn = AAssetManager_fromJava(env, assetManager);
    FileUtil::setAAssetManager(aamIn);
    init();
}

void Render::changeEs(int width, int height) {
    LOGD("~~~changeEs()~~~");
    glViewport(0, 0, width, height);
    _triangle->change();
}

void Render::drawEs() {
    LOGD("~~~drawEs()~~~");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _triangle->draw();
}


#ifdef __cplusplus
}
#endif