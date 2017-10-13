//
// Created by 70889 on 2017/9/27.
//
#include <stdlib.h>
#include "RenderUtil.h"
#include "Debug.h"
#include "FileUtil.h"

GLuint RenderUtil::program = 0;
GLuint RenderUtil::textureId = 0;

void RenderUtil::checkGLError(const char *op) {
    LOGD("~~~checkGLError()~~~\n");
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

GLuint RenderUtil::loadShader(GLenum type, const char *shaderCode) {
    LOGD("~~~loadShader()~~~\n");
    GLuint shader = glCreateShader(type);
    if (shader) {
        glShaderSource(shader, 1, &shaderCode, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc(sizeof(char) * infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Counld not compile shader %d:\n%s\n", shader, buf);
                }
                free(buf);
            }
            glDeleteShader(shader);
            shader = 0;
        }
    }
    return shader;
}

GLuint RenderUtil::createProgram(const char *vertexCode, const char *fragmentCode) {
    LOGD("~~~createProgram()~~~\n");
    GLuint vertextShader = loadShader(GL_VERTEX_SHADER, vertexCode);
    if (!vertextShader) {
        return 0;
    }

    GLuint framentShader = loadShader(GL_FRAGMENT_SHADER, fragmentCode);
    if (!framentShader) {
        return 0;
    }

    program = glCreateProgram();

    if (program) {
        glAttachShader(program, vertextShader);
        checkGLError("glAttachShader");
        glAttachShader(program, framentShader);
        checkGLError("glAttachShader");
        glLinkProgram(program);
        glDetachShader(program, vertextShader);
        glDetachShader(program, framentShader);
        glDeleteShader(vertextShader);
        glDeleteShader(framentShader);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint infoLen = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = (char *) malloc(sizeof(char) * infoLen);
                if (buf) {
                    glGetProgramInfoLog(program, infoLen, NULL, buf);
                    LOGE("Counld not link program:\n%s\n", buf);
                }
                free(buf);
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint RenderUtil::createTexture(const char *fileName) {
    LOGD("~~~loadTextrues()~~~\n");
    gl_texture_t *texinfo = NULL;
    GLuint *textures = new GLuint[1];
    glGenTextures(1, textures);
    checkGLError("glGenTextures");
    textureId = textures[0];

/*
    char *ext = strrchr(fileName, '.');
    if (ext) {
        ext++;
        if (!strcmp(ext, "png")) {
            texinfo = FileUtil::getPNGFromAsset(fileName);
        } else {
            texinfo = FileUtil::getOtherImangeFromAsset(fileName);
        }
    }
*/

    texinfo = FileUtil::getOtherImangeFromAsset(fileName);

    if ((0 != textureId) && (NULL != texinfo)) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        checkGLError("glBindTexture");
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        checkGLError("glTexParameterf");
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        checkGLError("glTexParameterf");
        glTexImage2D(GL_TEXTURE_2D, 0, texinfo->internalFormat, texinfo->width, texinfo->height, 0,
                     texinfo->format, GL_UNSIGNED_BYTE, texinfo->texels);
        checkGLError("glTexImage2D");
    }

    if (NULL != texinfo) {
        if (NULL != texinfo->texels) {
            free(texinfo->texels);
        }
        free(texinfo);
    }
    return textureId;
}

GLuint RenderUtil::getFinalProgram() {
    LOGD("~~~getFinalProgram()~~~\n");
    return program;
}

GLuint RenderUtil::getFinalTexture() {
    LOGD("~~~getFinalTexture()~~~\n");
    return textureId;
}
