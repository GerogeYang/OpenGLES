//
// Created by 70889 on 2017/9/27.
//
#include <stdlib.h>
#include "RenderUtil.h"
#include "Debug.h"
#include "../lodepng/lodepng.h"


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

bool RenderUtil::loadPNGImage(const char *fileName) {
    LOGD("~~~loadPNGImage()~~~\n");
    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned internalformat, format;

    unsigned error = lodepng::decode(image, width, height, fileName);

    if (error) {
        LOGE("~~~decode PNG Image failed, error code: %d\n~~~", error);
        return false;
    }

    internalformat = GL_RGBA;
    format = GL_RGBA;
    if (0 != textureId) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        checkGLError("glBindTexture");
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        checkGLError("glTexParameterf");
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        checkGLError("glTexParameterf");
        glTexImage2D(GL_TEXTURE_2D, 0, internalformat, width, height, 0, format,
                     GL_UNSIGNED_BYTE, &image[0]);
        checkGLError("glTexImage2D");
        return true;
    }
    return false;
}

/*bool RenderUtil::parseImage(const char *fileName, int &width, int &height, unsigned char *image) {
    AAsset *asset = FileUtil::openFromAsset(fileName);
    int fd = FileUtil::getFdFromAsset(asset);
    image = SOIL_load_image_from_fd(fd, &width, &height, 0, SOIL_LOAD_RGBA);
    LOGI("~~~YJ: width = %d, height = %d~~~",width, height);
    FileUtil::closeFromAsset(asset);
    if (NULL == image) {
        LOGE("~~~YJ: image = %s failed ~~~\n",image);
        return false;
    }
    LOGD("~~~YJ: image = %s~~~\n",image);
    return true;
}*/

GLuint RenderUtil::createTexture(const char *fileName) {
    LOGD("~~~createTexture()~~~\n");
    bool reslut;
    GLuint *textures = new GLuint[1];
    glGenTextures(1, textures);
    checkGLError("glGenTextures");
    textureId = textures[0];

    reslut = loadPNGImage(fileName);

    if(!reslut || (0 == textureId)){
        return 0;
    }

/*
    unsigned char *image = NULL;
    int width, height;
    reslut = parseImage(fileName, width, height, image);

    if(!reslut || (0 == textureId)){
        return 0;
    }

    glBindTexture(GL_TEXTURE_2D, textureId);
    checkGLError("glBindTexture");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    checkGLError("glTexParameterf");
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    checkGLError("glTexParameterf");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    checkGLError("glTexImage2D");
    SOIL_free_image_data(image);
*/

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
