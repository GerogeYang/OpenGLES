//
// Created by root on 17-9-30.
//

#include <malloc.h>
#include "Cube.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"
#include "../util/RenderUtil.h"
#include "../matrix/Matrix.h"

static GLfloat vertices[] = {
        -1.0f, 1.0f, 1.0f,    //正面左上0
        -1.0f, -1.0f, 1.0f,   //正面左下1
        1.0f, -1.0f, 1.0f,    //正面右下2
        1.0f, 1.0f, 1.0f,     //正面右上3
        -1.0f, 1.0f, -1.0f,    //反面左上4
        -1.0f, -1.0f, -1.0f,   //反面左下5
        1.0f, -1.0f, -1.0f,    //反面右下6
        1.0f, 1.0f, -1.0f,     //反面右上7
};

static GLfloat colors[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
};

static GLfloat ligtOAmbients[] = {1.0f, 1.0f, 1.0f, 1.0f};

static GLushort indexs[] = {
        0, 3, 2, 0, 2, 1,    //正面
        0, 1, 5, 0, 5, 4,    //左面
        0, 7, 3, 0, 4, 7,    //上面
        6, 7, 4, 6, 4, 5,    //后面
        6, 3, 7, 6, 2, 3,    //右面
        6, 5, 1, 6, 1, 2     //下面
};

Cube::Cube() : vertexShaderCode(NULL), fragmentShaderCode(NULL), mMatrixHandle(0),
               mPositionHandle(0), mColorHandle(0), mLightAmbientHandle(0),
               mProjectMatrix(NULL), mViewMatrix(NULL), mMVPMatrix(NULL) {
    mProjectMatrix = new GLfloat[16];
    mViewMatrix = new GLfloat[16];
    mMVPMatrix = new GLfloat[16];
}

Cube::~Cube() {
    LOGD("~~~destorySquare()~~~\n");
    if (NULL != vertexShaderCode) {
        free(vertexShaderCode);
        vertexShaderCode = NULL;
    }

    if (NULL != fragmentShaderCode) {
        free(fragmentShaderCode);
        fragmentShaderCode = NULL;
    }

    if (NULL != mProjectMatrix) {
        delete mProjectMatrix;
        mProjectMatrix = NULL;
    }

    if (NULL != mViewMatrix) {
        delete mViewMatrix;
        mViewMatrix = NULL;
    }

    if (NULL != mMVPMatrix) {
        delete mMVPMatrix;
        mMVPMatrix = NULL;
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
    float ratio = (float) width / height;
    Matrix::frustumM(mProjectMatrix, 0, -ratio, ratio, -1, 1, 3, 200);
    Matrix::setLookAtM(mViewMatrix, 0, 5.0f, 5.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    Matrix::multiplyMM(mMVPMatrix, 0, mProjectMatrix, 0, mViewMatrix, 0);
}

void Cube::draw() {
    LOGD("~~~draw()~~~\n");
    glUseProgram(program);
    mMatrixHandle = (GLuint) glGetUniformLocation(program, "vMatrix");
    glUniformMatrix4fv(mMatrixHandle, 1, GL_FALSE, mMVPMatrix);

    mPositionHandle = (GLuint) glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                          COORDS_PER_VERTEX * sizeof(GLfloat), vertices);

    mColorHandle = (GLuint) glGetAttribLocation(program, "aColor");
    glEnableVertexAttribArray(mColorHandle);
    glVertexAttribPointer(mColorHandle, COORDS_PER_COLORS, GL_FLOAT, GL_FALSE,
                          COORDS_PER_COLORS * sizeof(GLfloat), colors);

    mLightAmbientHandle = (GLuint) glGetAttribLocation(program, "aAmbient");
    glEnableVertexAttribArray(mLightAmbientHandle);
    glVertexAttribPointer(mLightAmbientHandle, 4, GL_FLOAT, GL_FALSE,
                          0, ligtOAmbients);


    glDrawElements(GL_TRIANGLES, sizeof(indexs) / sizeof(GLushort), GL_UNSIGNED_SHORT, indexs);

    glDisableVertexAttribArray(mMatrixHandle);
    glDisableVertexAttribArray(mPositionHandle);
    glDisableVertexAttribArray(mColorHandle);
    glDisableVertexAttribArray(mLightAmbientHandle);
}