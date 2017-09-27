//
// Created by 70889 on 2017/9/25.
//

#ifndef OPENGLES_MATRIXSTATE_H
#define OPENGLES_MATRIXSTATE_H



class MatrixState {
private:
    static float mProjectMatrix[16];
    static float mVMatrix[16];
public:
    void setCamera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ,
                   float upX, float upY, float upZ);
};


#endif //OPENGLES_MATRIXSTATE_H
