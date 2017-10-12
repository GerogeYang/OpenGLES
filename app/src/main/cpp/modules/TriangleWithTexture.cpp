//
// Created by root on 17-10-12.
//

#include <malloc.h>
#include "TriangleWithTexture.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"
#include "../util/ShaderUtil.h"
#include "../matrixstate/MatrixState.h"
#include "../util/TextureUtil.h"

static GLfloat vertices[] = {
        1.0f, 1.0f, 0.0f,// top right
        -1.0f, -1.0f, 0.0f,// bottom left
        1.0f, -1.0f, 0.0f // bottom right
};

static GLfloat colors[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
};

static GLfloat normals[] = {
        2.0f, 4.0f, 0.0f,
        -4.0f, -2.0f, 0.0f,
        2.0f, -2.0f, 0.0f,
};

static GLfloat textCoords[] = {
        0.5f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
};

static GLushort indexs[] = {
        0, 1, 2  //逆时针绘图
};

TriangleWithTexture::TriangleWithTexture() : vertexShaderCode(NULL), fragmentShaderCode(NULL), mMMatrix(NULL), mMVPMatrix(NULL),
                                             program(0),textureId(0), mMMatrixHandle(0), mMVPMatrixHandle(0), mCameraHandle(0), mLightHandle(0),
                                             mPositionHandle(0), mNormalHandle(0), mColorHandle(0), mTextCoordHandle(0),
                                             tx(0.0), ty(0.0), tz(0.0), rot(0.0), sx(1.0), sy(1.0), sz(1.0) {
}

TriangleWithTexture::~TriangleWithTexture() {
    LOGD("~~~destoryTriangleWithTexture()~~~\n");
    if (NULL != vertexShaderCode) {
        free(vertexShaderCode);
        vertexShaderCode = NULL;
    }

    if (NULL != fragmentShaderCode) {
        free(fragmentShaderCode);
        fragmentShaderCode = NULL;
    }
}

void TriangleWithTexture::initShader() {
    LOGD("~~~initShader()~~~\n");
    vertexShaderCode = FileUtil::getStrFromAsset("vertext.glsl");
    fragmentShaderCode = FileUtil::getStrFromAsset("fragment.glsl");
    program = ShaderUtil::createProgram(vertexShaderCode, fragmentShaderCode);
}

void TriangleWithTexture::initTextures() {
    LOGD("~~~initTextures()~~~\n");
    textureId = TextureUtil::loadTextures("1.png");
}

void TriangleWithTexture::initHandle() {
    LOGD("~~~initHandle()~~~\n");
    glUseProgram(program);
    mCameraHandle = (GLuint) glGetUniformLocation(program, "uCamera");
    mLightHandle = (GLuint) glGetUniformLocation(program, "uLightDirection");
    mMMatrixHandle = (GLuint) glGetUniformLocation(program, "uMMatrix");
    mMVPMatrixHandle = (GLuint) glGetUniformLocation(program, "uMVPMatrix");
    mPositionHandle = (GLuint) glGetAttribLocation(program, "aPosition");
    mNormalHandle = (GLuint) glGetAttribLocation(program, "aNormal");
    mColorHandle = (GLuint) glGetAttribLocation(program, "aColor");
}

void TriangleWithTexture::init() {
    LOGD("~~~init()~~~\n");
    initShader();
    initTextures();
    initHandle();
}

void TriangleWithTexture::change() {
    LOGD("~~~change()~~~\n");
}

void TriangleWithTexture::setMMatrix() {
    LOGD("~~~setMMatrix()~~~\n");
}

void TriangleWithTexture::draw() {
    LOGD("~~~draw()~~~\n");
    setMMatrix();

    glUseProgram(program);
    glUniform3fv(mCameraHandle, 1, MatrixState::getCameraLocation());
    glUniform3fv(mLightHandle, 1, MatrixState::getLightLocation());
    glUniformMatrix4fv(mMMatrixHandle, 1, GL_FALSE, MatrixState::getMMatrix());
    glUniformMatrix4fv(mMVPMatrixHandle, 1, GL_FALSE, MatrixState::getFinalMVPMatrix());

    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                          COORDS_PER_VERTEX * sizeof(GLfloat), vertices);

    glEnableVertexAttribArray(mNormalHandle);
    glVertexAttribPointer(mNormalHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                          COORDS_PER_VERTEX * sizeof(GLfloat), normals);

    glEnableVertexAttribArray(mColorHandle);
    glVertexAttribPointer(mColorHandle, COORDS_PER_COLORS, GL_FLOAT, GL_FALSE,
                          COORDS_PER_COLORS * sizeof(GLfloat), colors);

    glEnableVertexAttribArray(mTextCoordHandle);
    glVertexAttribPointer(mTextCoordHandle, COORDS_PER_TTEXTURES, GL_FLOAT, GL_FALSE,
                          COORDS_PER_TTEXTURES * sizeof(GLfloat), textCoords);

    glDrawElements(GL_TRIANGLES, sizeof(indexs) / sizeof(GLushort), GL_UNSIGNED_SHORT, indexs);

    glDisableVertexAttribArray(mPositionHandle);
    glDisableVertexAttribArray(mNormalHandle);
    glDisableVertexAttribArray(mColorHandle);
    glDisableVertexAttribArray(mTextCoordHandle);
}
