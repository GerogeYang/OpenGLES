//
// Created by root on 17-10-12.
//

#ifndef OPENGLES_TRIANGLEWITHTEXTURE_H
#define OPENGLES_TRIANGLEWITHTEXTURE_H


#include <GLES2/gl2.h>
#include "BaseShape.h"

class TriangleWithTexture: public BaseShape {

private:
    static const int COORDS_PER_VERTEX = 3;

    static const int COORDS_PER_COLORS = 4;

    static const int COORDS_PER_TEXTURES = 2;

    GLuint program;

    GLuint textureId;

    GLuint mMMatrixHandle;

    GLuint mMVPMatrixHandle;

    GLuint mCameraHandle;

    GLuint mLightHandle;

    GLuint mPositionHandle;

    GLuint mNormalHandle;

    GLuint mColorHandle;

    GLuint mTextureCoordHandle;

    GLfloat *mMMatrix;

    GLfloat *mMVPMatrix;

    float tx,ty,tz,rot,sx,sy,sz;

    void initShader();

    void initTextures();

    void initHandle();

    void setMMatrix();

public:
    TriangleWithTexture();

    ~TriangleWithTexture();

    void init();

    void change();

    void draw();
};


#endif //OPENGLES_TRIANGLEWITHTEXTURE_H
