//
// Created by 70889 on 2017/9/22.
//

#ifndef OPENGLES_ES_H
#define OPENGLES_ES_H

#include <jni.h>
#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <GLES/gl.h>
#include "../modules/Triangle.h"

class Render {
private:
    Triangle *_triangle;

    void printGLString(const char *name, GLenum s);

    void init();

public:
    Render();

    ~Render();

    void createEs(JNIEnv *env, jobject assetManager);

    void changeEs(int width, int height);

    void drawEs();

};


#endif //OPENGLES_ES_H
