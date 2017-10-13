//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_RENDERUTIL_H
#define OPENGLES_RENDERUTIL_H


#include <GLES2/gl2.h>

class RenderUtil {
private:
    static GLuint program;

    static GLuint textureId;

    static void checkGLError(const char *op);

    static GLuint loadShader(GLenum type, const char *shaderCode);

public:
    static GLuint createProgram(const char *vertexCode, const char *fragmentCode);

    static GLuint createTexture(const char *fileName);

    static GLuint getFinalProgram();

    static GLuint getFinalTexture();

};


#endif //OPENGLES_RENDERUTIL_H
