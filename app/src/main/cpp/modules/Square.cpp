//
// Created by root on 17-9-30.
//

#include <malloc.h>
#include "Square.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"
#include "../util/RenderUtil.h"
#include "../matrixstate/MatrixState.h"

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


Square::Square() : vertexShaderCode(NULL), fragmentShaderCode(NULL), mMMatrix(NULL), mMVPMatrix(NULL),
                   program(0), mMMatrixHandle(0), mMVPMatrixHandle(0), mCameraHandle(0),
                   mLightHandle(0), mPositionHandle(0), mNormalHandle(0), mColorHandle(0),
                   tx(0.0), ty(0.0), tz(0.0), rot(0.0), sx(1.0), sy(1.0), sz(1.0) {
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
}

void Square::init() {
    LOGD("~~~init()~~~\n");
    vertexShaderCode = FileUtil::getStrFromAsset("vertext.glsl");
    fragmentShaderCode = FileUtil::getStrFromAsset("fragment.glsl");
    program = RenderUtil::createProgram(vertexShaderCode, fragmentShaderCode);
}

void Square::change() {
    LOGD("~~~change()~~~\n");

}

void Square::setMMatrix() {
    LOGD("~~~setMMatrix()~~~\n");
    MatrixState::rotate(rot, 0.0, 0.0, 1.0);
    if (rot < 360) {
        rot += 5;
    } else {
        rot = 0;
    }
}

void Square::draw() {
    LOGD("~~~draw()~~~\n");
    setMMatrix();

    glUseProgram(program);

    mMVPMatrixHandle = (GLuint) glGetUniformLocation(program, "uMVPMatrix");
    glUniformMatrix4fv(mMVPMatrixHandle, 1, GL_FALSE, MatrixState::getFinalMVPMatrix());

    mPositionHandle = (GLuint) glGetAttribLocation(program, "aPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                          COORDS_PER_VERTEX * sizeof(GLfloat), vertices);

    mColorHandle = (GLuint) glGetAttribLocation(program, "aColor");
    glEnableVertexAttribArray(mColorHandle);
    glVertexAttribPointer(mColorHandle, COORDS_PER_COLORS, GL_FLOAT, GL_FALSE,
                          0, colors);

    //glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / COORDS_PER_VERTEX);
    glDrawElements(GL_TRIANGLES, sizeof(indexs) / sizeof(GLushort), GL_UNSIGNED_SHORT, indexs);

    glDisableVertexAttribArray(mPositionHandle);
    glDisableVertexAttribArray(mColorHandle);
}