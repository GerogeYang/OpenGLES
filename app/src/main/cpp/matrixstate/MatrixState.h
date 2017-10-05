//
// Created by 70889 on 2017/9/25.
//

#ifndef OPENGLES_MATRIXSTATE_H
#define OPENGLES_MATRIXSTATE_H


class MatrixState {
private:
    static int stackTop;

    static GLfloat **mStack;

    static GLfloat *mCurMatrix;

    static GLfloat *mViewMatrix;

    static GLfloat *mProjectMatrix;

    static GLfloat *mMVPMatrix;

    static GLfloat *cameraLocation;

    static GLfloat *lightLocation;

    static void setInitStack();

public:
    static void init();

    static void pushMatrix();

    static void popMatrix();

    static void translate(float x, float y, float z);

    static void rotate(float angle, float x, float y, float z);

    static void scale(float x, float y, float z);

    static void
    setCamera(float eyeX, float eyeY, float eyeZ,
              float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

    static void setLightLocation(float x, float y, float z);

    static void
    setProjectFrustum(float left, float right, float bottom, float top, float near, float far);

    static void
    setProjectOrtho(float left, float right, float bottom, float top, float near, float far);

    static void matrix(GLfloat *self);

    static GLfloat *getCameraLocation();

    static GLfloat *getLightLocation();

    static GLfloat *getMixMatrix();

    static GLfloat *getFinalMVPMatrix();

    static void destoryMatrixState();
};


#endif //OPENGLES_MATRIXSTATE_H
