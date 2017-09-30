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

    GLuint mPositionHandle;

    GLuint mColorHandle;

    GLuint mMatrixHandle;

    GLfloat *mViewMatrix;

    GLfloat *mProjectMatrix;

    GLfloat *mMVPMatrix;

public:
    Square();

    ~Square();

    void init();

    void change(int width, int height);

    void draw();
};


#endif //OPENGLES_SQUARE_H
