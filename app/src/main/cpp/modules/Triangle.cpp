//
// Created by 70889 on 2017/9/22.
//

#include <GLES/gl.h>
#include <malloc.h>
#include "Triangle.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"
#include "../util/RenderUtil.h"
#include "../matrix/Matrix.h"


static GLfloat vertices[] = {
        0.5f, 0.5f, 0.0f, // top
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f  // bottom right
};

GLfloat colors[] = {1.0f, 0.0f, 1.0f, 1.0f};


Triangle::Triangle() : vertexShaderCode(NULL), fragmentShaderCode(NULL), mPositionHandle(0),
                       mColorHandle(0), mMatrixHandle(0), mProjectMatrix(NULL), mViewMatrix(NULL),
                       mMVPMatrix(NULL) {
    mProjectMatrix = new GLfloat[16];
    mViewMatrix = new GLfloat[16];
    mMVPMatrix = new GLfloat[16];
}

Triangle::~Triangle() {
    LOGD("~~~DestoryTriangle()~~~\n");
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

void Triangle::init() {
    LOGD("~~~init()~~~\n");
    vertexShaderCode = FileUtil::getStrFromAsset("vertextSource.glsl");
    fragmentShaderCode = FileUtil::getStrFromAsset("fragmentSource.glsl");
    program = RenderUtil::createProgram(vertexShaderCode, fragmentShaderCode);
}

void Triangle::change(int width, int height) {
    LOGD("~~~change()~~~\n");
    float ratio = (float) width / height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    Matrix::frustumM(mProjectMatrix, 0, -ratio, ratio, -1, 1, 3, 7);
    Matrix::setLookAtM(mViewMatrix, 0.0f, 0.0f, 0.0f, 7.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    Matrix::multiplyMM(mMVPMatrix, 0, mProjectMatrix, 0, mViewMatrix, 0);
}

void Triangle::draw() {
    LOGD("~~~draw()~~~\n");
    glUseProgram(program);
    mMatrixHandle = (GLuint)glGetUniformLocation(program, "vMatrix");
    glUniformMatrix4fv(mMatrixHandle, 1, false, mMVPMatrix);

    mPositionHandle = (GLuint) glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
                          COORDS_PER_VERTEX * sizeof(GLfloat), vertices);
    mColorHandle = (GLuint) glGetUniformLocation(program, "vColor");
    glUniform4fv(mColorHandle, 1, colors);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / COORDS_PER_VERTEX);
    glDisableVertexAttribArray(mPositionHandle);
}