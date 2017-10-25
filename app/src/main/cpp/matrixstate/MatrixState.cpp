//
// Created by 70889 on 2017/9/25.
//

#include <GLES/gl.h>
#include "MatrixState.h"
#include "../matrix/Matrix.h"
#include "../util/include/Debug.h"

int MatrixState::stackTop = -1;
GLfloat **MatrixState::mStack;
GLfloat *MatrixState::mCurMatrix;
GLfloat *MatrixState::mViewMatrix;
GLfloat *MatrixState::mProjectMatrix;
GLfloat *MatrixState::mMVPMatrix;
GLfloat *MatrixState::cameraLocation;
GLfloat *MatrixState::lightLocation;

void MatrixState::setInitStack() {
    mStack = new GLfloat *[10];
    for (int i = 0; i < 10; ++i) {
        mStack[i] = new GLfloat[16];
    }
}

void MatrixState::init() {
    setInitStack();
    mCurMatrix = new GLfloat[16];
    mViewMatrix = new GLfloat[16];
    mProjectMatrix = new GLfloat[16];
    mMVPMatrix = new GLfloat[16];
    cameraLocation = new GLfloat[3];
    lightLocation = new GLfloat[3];
    Matrix::setRotateM(mCurMatrix, 0, 0, 1, 0, 0);
}

void MatrixState::pushMatrix() {
    stackTop++;
    for (int i = 0; i < 16; i++) {
        mStack[stackTop][i] = mCurMatrix[i];
    }
}

void MatrixState::popMatrix() {
    for (int i = 0; i < 16; i++) {
        mCurMatrix[i] = mStack[stackTop][i];
    }
    stackTop--;
}

void MatrixState::translate(float x, float y, float z) {
    Matrix::translateM(mCurMatrix, 0, x, y, z);
}

void MatrixState::rotate(float angle, float x, float y, float z) {
    Matrix::rotateM(mCurMatrix, 0, angle, x, y, z);
}

void MatrixState::scale(float x, float y, float z) {
    Matrix::scaleM(mCurMatrix, 0, x, y, z);
}

void MatrixState::setCamera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY,
                            float centerZ,
                            float upX, float upY, float upZ) {
    Matrix::setLookAtM(mViewMatrix, 0, eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    cameraLocation[0] = eyeX;
    cameraLocation[1] = eyeY;
    cameraLocation[2] = eyeZ;
}

void MatrixState::setLightLocation(float x, float y, float z) {
    lightLocation[0] = x;
    lightLocation[1] = y;
    lightLocation[2] = z;
}

void MatrixState::setProjectFrustum(float left, float right, float bottom, float top, float near,
                                    float far) {
    Matrix::frustumM(mProjectMatrix, 0, left, right, bottom, top, near, far);
}

void MatrixState::setProjectOrtho(float left, float right, float bottom, float top, float near,
                                  float far) {
    Matrix::orthoM(mProjectMatrix, 0, left, right, top, bottom, near, far);
}

void MatrixState::matrix(GLfloat *self) {
    Matrix::multiplyMM(mCurMatrix, 0, self, 0, mCurMatrix, 0);
}

GLfloat *MatrixState::getCameraLocation() {
    return cameraLocation;
}

GLfloat *MatrixState::getLightLocation() {
    return lightLocation;
}

GLfloat *MatrixState::getMMatrix() {
    return mCurMatrix;
}

GLfloat *MatrixState::getFinalMVPMatrix() {
    Matrix::multiplyMM(mMVPMatrix, 0, mViewMatrix, 0, mCurMatrix, 0);
    Matrix::multiplyMM(mMVPMatrix, 0, mProjectMatrix, 0, mMVPMatrix, 0);
    return mMVPMatrix;
}

void MatrixState::destoryMatrixState() {
    LOGD("~~~destoryMatrixState()~~~\n");
    if (NULL != mStack) {
        for (int i = 0; i < 10; i++) {
            delete[] mStack[i];
        }
        delete[] mStack;
    }

    if (NULL != mCurMatrix) {
        delete[] mCurMatrix;
        mCurMatrix = NULL;
    }

    if (NULL != mViewMatrix) {
        delete[] mViewMatrix;
        mViewMatrix = NULL;
    }

    if (NULL != mProjectMatrix) {
        delete[] mProjectMatrix;
        mProjectMatrix = NULL;
    }

    if (NULL != mMVPMatrix) {
        delete[] mMVPMatrix;
        mMVPMatrix = NULL;
    }

    if (NULL != cameraLocation) {
        delete[] cameraLocation;
        cameraLocation = NULL;
    }

    if (NULL != lightLocation) {
        delete[] lightLocation;
        lightLocation = NULL;
    }
}