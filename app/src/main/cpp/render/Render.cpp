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


Render::Render() : _triangle(NULL),_square(NULL) {
    _triangle = new Triangle();
    _square = new Square();
}

Render::~Render() {
    LOGD("~~~destoryRender()~~~\n");
    if (NULL != _triangle) {
        delete _triangle;
        _triangle = NULL;
    }

    if (NULL != _square) {
        delete _square;
        _square = NULL;
    }
}

void Render::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

void Render::init() {
    LOGD("~~~init()~~~\n");
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
    glClearColor(0, 0, 0, 0);
    _square->init();
}

void Render::createEs(JNIEnv *env, jobject assetManager) {
    LOGD("~~~createEs()~~~\n");
    AAssetManager *aamIn = AAssetManager_fromJava(env, assetManager);
    FileUtil::setAAssetManager(aamIn);
    init();
}

void Render::changeEs(int width, int height) {
    LOGD("~~~changeEs()~~~\n");
    glViewport(0, 0, width, height);
    _square->change(width, height);
}

void Render::drawEs() {
    LOGD("~~~drawEs()~~~\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    _square->draw();
}


#ifdef __cplusplus
}
#endif