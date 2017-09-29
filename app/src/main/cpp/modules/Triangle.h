//
// Created by 70889 on 2017/9/22.
//

#ifndef OPENGLES_TRIANGLE_H
#define OPENGLES_TRIANGLE_H

#include "BaseShape.h"

class Triangle : public BaseShape {
private:
    static const int COORDS_PER_VERTEX = 3;

    char *vertexShaderCode;

    char *fragmentShaderCode;

    GLuint program;

    GLuint mPositionHandle;

    GLuint mColorHandle;

    GLuint mMatrixHandle;

public:
    Triangle();

    ~Triangle();

    void init();

    void change();

    void draw();
};


#endif //OPENGLES_TRIANGLE_H
