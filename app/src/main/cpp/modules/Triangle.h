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

    GLuint mPositionHandle;

    GLuint mColorHandle;

    GLuint mMatrixHandle;

    GLfloat *mViewMatrix;

    GLfloat *mProjectMatrix;

    GLfloat *mMVPMatrix;

public:
    Triangle();

    ~Triangle();

    void init();

    void change(int width, int height);

    void draw();
};


#endif //OPENGLES_TRIANGLE_H
