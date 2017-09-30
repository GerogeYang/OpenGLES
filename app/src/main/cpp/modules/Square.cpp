//
// Created by root on 17-9-30.
//

#include <malloc.h>
#include "Square.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"
#include "../util/RenderUtil.h"
#include "../matrix/Matrix.h"

static GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,// top right
        -0.5f, 0.5f, 0.0f,//top left
        -0.5f, -0.5f, 0.0f,// bottom left
        0.5f, -0.5f, 0.0f // bottom right
};

static GLfloat colors[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 1.0f
};

static GLushort indexs[] = {
        0, 1, 3, 1, 2, 3  //逆时针绘图
};


Square::Square() : vertexShaderCode(NULL), fragmentShaderCode(NULL), mPositionHandle(0),
                   mColorHandle(0), mMatrixHandle(0), mProjectMatrix(NULL), mViewMatrix(NULL),
                   mMVPMatrix(NULL) {
    mProjectMatrix = new GLfloat[16];
    mViewMatrix = new GLfloat[16];
    mMVPMatrix = new GLfloat[16];
}

Square::~Square() {
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

void Square::init() {
    LOGD("~~~init()~~~\n");
    vertexShaderCode = FileUtil::getStrFromAsset("vertextSource.glsl");
    fragmentShaderCode = FileUtil::getStrFromAsset("fragmentSource.glsl");
    program = RenderUtil::createProgram(vertexShaderCode, fragmentShaderCode);
}

void Square::change(int width, int height) {
    LOGD("~~~change()~~~\n");
    float ratio = (float) width / height;
    Matrix::frustumM(mProjectMatrix, 0, -ratio, ratio, -1, 1, 3, 100);
    Matrix::setLookAtM(mViewMatrix, 0, 0.0f, 0.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    Matrix::multiplyMM(mMVPMatrix, 0, mProjectMatrix, 0, mViewMatrix, 0);
}

void Square::draw() {
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
                          0, colors);

    //glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / COORDS_PER_VERTEX);
    glDrawElements(GL_TRIANGLES, sizeof(indexs) / sizeof(GLushort), GL_UNSIGNED_SHORT, indexs);

    glDisableVertexAttribArray(mMatrixHandle);
    glDisableVertexAttribArray(mPositionHandle);
    glDisableVertexAttribArray(mColorHandle);
}