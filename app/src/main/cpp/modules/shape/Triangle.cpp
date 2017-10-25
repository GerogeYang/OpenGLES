//
// Created by 70889 on 2017/9/22.
//

#include <malloc.h>
#include <util/Debug.h>
#include <util/RenderUtil.h>
#include <matrix/MatrixState.h>
#include <shape/Triangle.h>


static GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f,// top right
        -0.5f, -0.5f, 0.0f,// bottom left
        0.5f, -0.5f, 0.0f // bottom right
};

static GLfloat colors[] = {
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f
};

static GLushort indexs[] = {
        0, 1, 2  //逆时针绘图
};

Triangle::Triangle() : mMMatrix(NULL), mMVPMatrix(NULL),
                       program(0), mMMatrixHandle(0), mMVPMatrixHandle(0), mCameraHandle(0),
                       mLightHandle(0), mPositionHandle(0), mNormalHandle(0), mColorHandle(0),
                       tx(0.0), ty(0.0), tz(0.0), rot(0.0), sx(1.0), sy(1.0), sz(1.0) {

}

Triangle::~Triangle() {
    LOGD("~~~destoryTriangle()~~~\n");
}

void Triangle::init() {
    LOGD("~~~init()~~~\n");
    program = RenderUtil::createProgram("shader/vertext.glsl", "shader/fragment.glsl");
}

void Triangle::change() {
    LOGD("~~~change()~~~\n");

}

void Triangle::setMMatrix() {
    LOGD("~~~setMMatrix()~~~\n");
}

void Triangle::draw() {
    LOGD("~~~draw()~~~\n");
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