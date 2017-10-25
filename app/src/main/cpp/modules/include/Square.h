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
    Square();

    ~Square();

    void init();

    void change();

    void draw();
};


#endif //OPENGLES_SQUARE_H
