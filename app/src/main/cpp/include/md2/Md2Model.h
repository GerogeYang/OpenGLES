//
// Created by root on 17-12-11.
//

#ifndef OPENGLES_MD2MODEL_H
#define OPENGLES_MD2MODEL_H

#include <GLES2/gl2.h>
#include "Md2Header.h"

class Md2Model {
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

    GLuint mTextureCoordHandle;

    GLuint mColorHandle;

    float tx,ty,tz,rot,sx,sy,sz;

    Md2Header *_md2;

    void initShader();

    void initModelData();

    void initTextures();

    void initHandle();

    void updateMMatrix();

public:
    Md2Model();

    ~Md2Model();

    void init();

    void change();

    void draw();

};

#endif //OPENGLES_MD2MODEL_H
