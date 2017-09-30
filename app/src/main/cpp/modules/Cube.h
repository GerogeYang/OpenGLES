//
// Created by root on 17-9-30.
//

#ifndef OPENGLES_BALL_H
#define OPENGLES_BALL_H


#include "BaseShape.h"

class Cube : public BaseShape {
private:
    static const int COORDS_PER_VERTEX = 3;

    static const int COORDS_PER_COLORS = 4;

    char *vertexShaderCode;

    char *fragmentShaderCode;

    GLuint program;

    GLuint mMatrixHandle;

    GLuint mPositionHandle;

    GLuint mColorHandle;

    GLuint mLightAmbientHandle;

    GLfloat *mViewMatrix;

    GLfloat *mProjectMatrix;

    GLfloat *mMVPMatrix;

public:
    Cube();

    ~Cube();

    void init();

    void change(int width, int height);

    void draw();
};


#endif //OPENGLES_BALL_H
