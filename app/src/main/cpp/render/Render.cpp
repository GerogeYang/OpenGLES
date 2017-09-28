//
// Created by 7088"ES" on 2017/"ES"/22.
//

#include <GLES2/gl2.h>
#include <GLES/gl.h>
#include <jni.h>
#include <android/asset_manager_jni.h>
#include "Render.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"
#include "../util/RenderUtil.h"


#ifdef __cplusplus
extern "C" {
#endif

GLfloat vertexts[] = {
        0.0f, 1.0f, -3.0f,
        1.0f, 0.0f, -3.0f,
        -1.0f, 0.0f, -3.0f
};

GLfloat color[] = {1.0f, 1.0f, .5f, 1.0f};

char *vertexShaderCode;

char *fragmentShaderCode;

GLuint program;

GLuint mPositionHandle;

GLuint mColorHandle;

Render::Render() {

}

Render::~Render() {

}

void Render::init(JNIEnv *env, jobject assetManager) {
    LOGD("~~~init()~~~");
    AAssetManager *aamIn = AAssetManager_fromJava(env, assetManager);
    FileUtil::setAAssetManager(aamIn);
}

void Render::createEs(JNIEnv *env, jobject assetManager) {
    LOGD("~~~createEs()~~~");
    init(env, assetManager);
    glClearColor(1, 1, 1, 1);
    vertexShaderCode = FileUtil::getStrFromAsset("vertextSource.glsl");
    fragmentShaderCode = FileUtil::getStrFromAsset("fragmentSource.glsl");
    program = RenderUtil::createProgram(vertexShaderCode, fragmentShaderCode);
}

void Render::changeEs(int width, int height) {
    LOGD("~~~changeEs()~~~");
    glViewport(0, 0, width, height);
}

void Render::drawEs() {
    LOGD("drawEs()");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(program);
    mPositionHandle = (GLuint)glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, 3, GL_FLOAT, GL_FALSE, 3 * 4, vertexts);
    mColorHandle = (GLuint)glGetUniformLocation(program, "vColor");
    glUniform4fv(mColorHandle, 1, color);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    glDisableVertexAttribArray(mPositionHandle);
}


#ifdef __cplusplus
}
#endif