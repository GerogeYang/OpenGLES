//
// Created by root on 17-9-30.
//

#ifndef OPENGLES_SQUARE_H
#define OPENGLES_SQUARE_H


#include "BaseShape.h"

class Square : public BaseShape {
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

    GLfloat *mCamera;

    GLfloat *mLightLocation;

    float tx,ty,tz,rot,sx,sy,sz;

    void setMatrix();

public:
    Square();

    ~Square();

    void init();

    void change();

    void draw();
};


#endif //OPENGLES_SQUARE_H
