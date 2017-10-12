//
// Created by 70889 on 2017/9/22.
//

#ifndef OPENGLES_TRIANGLE_H
#define OPENGLES_TRIANGLE_H

#include "BaseShape.h"

class Triangle : public BaseShape {
private:
    static const int COORDS_PER_VERTEX = 3;

    static const int COORDS_PER_COLORS = 4;

    char *vertexShaderCode;

    char *fragmentShaderCode;

    GLuint program;

    GLuint mMMatrixHandle;

    GLuint mMVPMatrixHandle;

    GLuint mCameraHandle;

    GLuint mLightHandle;

    GLuint mPositionHandle;

    GLuint mNormalHandle;

    GLuint mColorHandle;

    GLfloat *mMMatrix;

    GLfloat *mMVPMatrix;

    float tx,ty,tz,rot,sx,sy,sz;

    void setMMatrix();

public:
    Triangle();

    ~Triangle();

    void init();

    void change();

    void draw();

};


#endif //OPENGLES_TRIANGLE_H
