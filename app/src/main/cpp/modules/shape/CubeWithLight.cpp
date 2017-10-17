//
// Created by root on 17-9-30.
//

#include <malloc.h>
#include <GLES/gl.h>
#include <CubeWithLight.h>
#include "../../util/Debug.h"
#include "../../util/FileUtil.h"
#include "../../util/RenderUtil.h"
#include "../../matrixstate/MatrixState.h"


static GLfloat vertices[] = {
        0.0f, -0.525731f, 0.850651f,
        0.850651f, 0.0f, 0.525731f,
        0.850651f, 0.0f, -0.525731f,
        -0.850651f, 0.0f, -0.525731f,
        -0.850651f, 0.0f, 0.525731f,
        -0.525731f, 0.850651f, 0.0f,
        0.525731f, 0.850651f, 0.0f,
        0.525731f, -0.850651f, 0.0f,
        -0.525731f, -0.850651f, 0.0f,
        0.0f, -0.525731f, -0.850651f,
        0.0f, 0.525731f, -0.850651f,
        0.0f, 0.525731f, 0.850651f,
};

static GLfloat colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.5f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f, 1.0f,
        0.5f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.5f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 0.5f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        0.5f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.5f, 1.0f,
};

static GLfloat normals[] = {
        0.0f, -0.417775f, 0.675974f,
        0.675973f, 0.0f, 0.417775f,
        0.675973f, -0.0f, -0.417775f,
        -0.675973f, 0.0f, -0.417775f,
        -0.675973f, 0.0f, 0.417775f,
        -0.417775f, 0.675974f, 0.0f,
        0.417775f, 0.675973f, 0.0f,
        0.417775f, -0.675974f, 0.0f,
        -0.417775f, -0.675974f, 0.0f,
        0.0f, -0.417775f, -0.675973f,
        0.0f, 0.417775f, -0.675974f,
        0.0f, 0.417775f, 0.675974f,
};

static GLushort indexs[] = {
        1, 2, 6,
        1, 7, 2,
        3, 4, 5,
        4, 3, 8,
        6, 5, 11,
        5, 6, 10,
        9, 10, 2,
        10, 9, 3,
        7, 8, 9,
        8, 7, 0,
        11, 0, 1,
        0, 11, 4,
        6, 2, 10,
        1, 6, 11,
        3, 5, 10,
        5, 4, 11,
        2, 7, 9,
        7, 1, 0,
        3, 9, 8,
        4, 8, 0,
};

static int STEP = 5;

CubeWithLight::CubeWithLight() : vertexShaderCode(NULL), fragmentShaderCode(NULL), mMMatrix(NULL), mMVPMatrix(NULL),
                                 program(0), mMMatrixHandle(0), mMVPMatrixHandle(0), mCameraHandle(0),
                                 mLightHandle(0), mPositionHandle(0), mNormalHandle(0), mColorHandle(0),
                                 tx(0.0), ty(0.0), tz(0.0), rot(0.0), sx(1.0), sy(1.0), sz(1.0) {
}

CubeWithLight::~CubeWithLight() {
    LOGD("~~~destoryCubeWithLight()~~~\n");
    if (NULL != vertexShaderCode) {
        free(vertexShaderCode);
        vertexShaderCode = NULL;
    }

    if (NULL != fragmentShaderCode) {
        free(fragmentShaderCode);
        fragmentShaderCode = NULL;
    }
}

void CubeWithLight::init() {
    LOGD("~~~init()~~~\n");
    vertexShaderCode = FileUtil::getStrFromAsset("shader/vertextWithLight.glsl");
    fragmentShaderCode = FileUtil::getStrFromAsset("shader/fragmentWithLight.glsl");
    program = RenderUtil::createProgram(vertexShaderCode, fragmentShaderCode);
}

void CubeWithLight::change() {
    LOGD("~~~change()~~~\n");

}

void CubeWithLight::setMMatrix() {
    LOGD("~~~setMMatrix()~~~\n");
    MatrixState::rotate(rot, 0.0, 1.0, 0.0);
    rot = ((int) rot + STEP) % 360;
}

void CubeWithLight::draw() {
    LOGD("~~~draw()~~~\n");
    setMMatrix();

    glUseProgram(program);

    mCameraHandle = (GLuint) glGetUniformLocation(program, "uCamera");
    glUniform3fv(mCameraHandle, 1, MatrixState::getCameraLocation());

    mLightHandle = (GLuint) glGetUniformLocation(program, "uLightDirection");
    glUniform3fv(mLightHandle, 1, MatrixState::getLightLocation());

    mMMatrixHandle = (GLuint) glGetUniformLocation(program, "uMMatrix");
    glUniformMatrix4fv(mMMatrixHandle, 1, GL_FALSE, MatrixState::getMMatrix());

    mMVPMatrixHandle = (GLuint) glGetUniformLocation(program, "uMVPMatrix");
    glUniformMatrix4fv(mMVPMatrixHandle, 1, GL_FALSE, MatrixState::getFinalMVPMatrix());

    mPositionHandle = (GLuint) glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                          COORDS_PER_VERTEX * sizeof(GLfloat), vertices);

    mNormalHandle = (GLuint) glGetAttribLocation(program, "aNormal");
    glEnableVertexAttribArray(mNormalHandle);
    glVertexAttribPointer(mNormalHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                          COORDS_PER_VERTEX * sizeof(GLfloat), normals);

    mColorHandle = (GLuint) glGetAttribLocation(program, "aColor");
    glEnableVertexAttribArray(mColorHandle);
    glVertexAttribPointer(mColorHandle, COORDS_PER_COLORS, GL_FLOAT, GL_FALSE,
                          COORDS_PER_COLORS * sizeof(GLfloat), colors);

    glDrawElements(GL_TRIANGLES, sizeof(indexs) / sizeof(GLushort), GL_UNSIGNED_SHORT, indexs);

    glDisableVertexAttribArray(mPositionHandle);
    glDisableVertexAttribArray(mNormalHandle);
    glDisableVertexAttribArray(mColorHandle);
}