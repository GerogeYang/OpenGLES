//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_RENDERUTIL_H
#define OPENGLES_RENDERUTIL_H

#include <GLES2/gl2.h>
#include <android/asset_manager.h>
#include <md2/Md2Header.h>

class RenderUtil {
private:
    static GLuint program;

    static GLuint textureId;

    static void checkGLError(const char *op);

    static GLuint loadShader(GLenum type, const char *shaderCode);

public:
    static void init(AAssetManager *mgr);

    static GLuint createProgram(const char *vertexFileName, const char *fragmentFileName);

    static GLuint createTexture(const char *fileName);

    static GLboolean loadMd2Model(const char *fileName, Md2Header* md2);

    static GLuint getFinalProgram();

    static GLuint getFinalTexture();

};


#endif //OPENGLES_RENDERUTIL_H
