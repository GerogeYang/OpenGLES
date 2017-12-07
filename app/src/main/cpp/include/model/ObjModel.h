//
// Created by root on 17-10-25.
//

#ifndef OPENGLES_OBJMODEL_H
#define OPENGLES_OBJMODEL_H


#include <GLES2/gl2.h>

class ObjModel {
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

    void initModelData();

    void initShader();

    void initHandle();

    void setMMatrix();

public:
    ObjModel();

    ~ObjModel();

    void init();

    void change();

    void draw();
};


#endif //OPENGLES_OBJMODEL_H
