//
// Created by 70889 on 2017/9/27.
//
#include <stdlib.h>
#include "ShaderUtil.h"
#include "Debug.h"

GLuint ShaderUtil::program = 0;

void ShaderUtil::checkGLError(const char *op) {
    LOGD("~~~checkGLError()~~~\n");
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

GLuint ShaderUtil::loadShader(GLenum type, const char *shaderCode) {
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

GLuint ShaderUtil::createProgram(const char *vertexCode, const char *fragmentCode) {
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

GLuint ShaderUtil::getFinalProgram() {
    LOGD("~~~getFinalProgram()~~~\n");
    return program;
}