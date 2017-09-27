//
// Created by root on 17-9-15.
//

#ifndef OPENGLES_MATRIX_H
#define OPENGLES_MATRIX_H

#include <math.h>

class Matrix {
public:
    static void multiplyMM(float* result, int resultOffset, float* mlIn, int lhsOffset, float* mrIn, int rhsOffset);
    static void multiplyMV (float* resultVec, int resultVecOffset, float* mlIn, int lhsMatOffset, float* vrIn, int rhsVecOffset);
    static void setIdentityM (float* sm, int smOffset);
    static void translateM(float* m, int mOffset,float x, float y, float z);
    static void rotateM(float* m, int mOffset,float a, float x, float y, float z);
    static void setRotateM(float* m, int mOffset,float a, float x, float y, float z);
    static void scaleM(float* m, int mOffset, float x, float y, float z);
    static void transposeM(float* mTrans, int mTransOffset, float* m, int mOffset);
    static void frustumM(float* m, int offset, float left, float right, float bottom, float top, float near, float far);
    static void setLookAtM(float* rm, int rmOffset, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
};


#endif //OPENGLES_MATRIX_H
