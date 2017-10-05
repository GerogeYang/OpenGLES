//
// Created by root on 17-9-30.
//

#include <malloc.h>
#include <GLES/gl.h>
#include "Cube.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"
#include "../util/RenderUtil.h"
#include "../matrixstate/MatrixState.h"


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

Cube::Cube() : vertexShaderCode(NULL), fragmentShaderCode(NULL),
               mMMatrixHandle(0), mMVPMatrixHandle(0), mCameraHandle(0), mLightHandle(0),
               mPositionHandle(0), mNormalHandle(0), mColorHandle(0),
               mMMatrix(NULL), mMVPMatrix(NULL), mCameraLocation(NULL), mLightLocation(NULL) {
}

Cube::~Cube() {
    LOGD("~~~destoryCube()~~~\n");
    if (NULL != vertexShaderCode) {
        free(vertexShaderCode);
        vertexShaderCode = NULL;
    }

    if (NULL != fragmentShaderCode) {
        free(fragmentShaderCode);
        fragmentShaderCode = NULL;
    }
}

void Cube::init() {
    LOGD("~~~init()~~~\n");
    vertexShaderCode = FileUtil::getStrFromAsset("cubeVertextSource.glsl");
    fragmentShaderCode = FileUtil::getStrFromAsset("cubeFragmentSource.glsl");
    program = RenderUtil::createProgram(vertexShaderCode, fragmentShaderCode);
}

void Cube::change(int width, int height) {
    LOGD("~~~change()~~~\n");
    mMMatrix = MatrixState::getMixMatrix();
    mMVPMatrix = MatrixState::getFinalMVPMatrix();
    mCameraLocation = MatrixState::getCameraLocation();
    mLightLocation = MatrixState::getLightLocation();
}

void Cube::draw() {
    LOGD("~~~draw()~~~\n");
    glUseProgram(program);
    mMMatrixHandle = (GLuint) glGetUniformLocation(program, "uMMatrix");
    glEnableVertexAttribArray(mMMatrixHandle);
    glUniformMatrix4fv(mMMatrixHandle, 1, GL_FALSE, mMMatrix);

    mMVPMatrixHandle = (GLuint) glGetUniformLocation(program, "uMVPMatrix");
    glEnableVertexAttribArray(mMVPMatrixHandle);
    glUniformMatrix4fv(mMVPMatrixHandle, 1, GL_FALSE, mMVPMatrix);

    mCameraHandle = (GLuint) glGetUniformLocation(program, "uCamera");
    glEnableVertexAttribArray(mCameraHandle);
    glUniform3fv(mCameraHandle, 1, mCameraLocation);

    mLightHandle = (GLuint) glGetUniformLocation(program, "ulightDirection");
    glEnableVertexAttribArray(mLightHandle);
    glUniform3fv(mLightHandle, 1, mLightLocation);

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

    glDisableVertexAttribArray(mMMatrixHandle);
    glDisableVertexAttribArray(mMVPMatrixHandle);
    glDisableVertexAttribArray(mCameraHandle);
    glDisableVertexAttribArray(mLightHandle);
    glDisableVertexAttribArray(mPositionHandle);
    glDisableVertexAttribArray(mNormalHandle);
    glDisableVertexAttribArray(mColorHandle);
}