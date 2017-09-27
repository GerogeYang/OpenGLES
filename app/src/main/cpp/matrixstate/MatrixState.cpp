//
// Created by 70889 on 2017/9/25.
//

#include <GLES/gl.h>
#include "MatrixState.h"
#include "../matrix/Matrix.h"

float MatrixState::mProjectMatrix[16];
float MatrixState::mVMatrix[16];

void MatrixState::setCamera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ,
               float upX, float upY, float upZ){
    Matrix::setLookAtM(mVMatrix, 0, 0, 0, 4, 0, 0, 0, 0, 1, 0);
}