//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_SHADERUTIL_H
#define OPENGLES_SHADERUTIL_H


#include <GLES2/gl2.h>

class ShaderUtil {
private:
    static GLuint program;

    static void checkGLError(const char *op);

    static GLuint loadShader(GLenum type, const char *shaderCode);

public:
    static GLuint createProgram(const char *vertexCode, const char *fragmentCode);

    static GLuint getFinalProgram();
};


#endif //OPENGLES_SHADERUTIL_H
