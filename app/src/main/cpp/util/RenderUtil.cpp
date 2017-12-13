//
// Created by 70889 on 2017/9/27.
//
#include <stdlib.h>
#include <util/Debug.h>
#include <util/FileUtil.h>
#include <util/RenderUtil.h>
#include <soil/SOIL.h>
#include <util/LoadUtil.h>

GLuint RenderUtil::program = 0;
GLuint RenderUtil::textureId = 0;

void RenderUtil::checkGLError(const char *op) {
    LOGD("~~~checkGLError()~~~\n");
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

void RenderUtil::init(AAssetManager *mgr) {
    LOGD("~~~init()~~~\n");
    FileUtil::init(mgr);
    SOIL_init(mgr);
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

GLuint RenderUtil::createProgram(const char *vertexFileName, const char *fragmentFileName) {
    LOGD("~~~createProgram()~~~\n");
    char *vertexCode = FileUtil::readFromAsset(vertexFileName);
    char *fragmentCode = FileUtil::readFromAsset(fragmentFileName);

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
    free(vertexCode);
    free(fragmentCode);
    return program;
}

GLuint RenderUtil::createTexture(const char *fileName) {
    LOGD("~~~createTexture()~~~\n");
    GLuint *textures = new GLuint[1];
    glGenTextures(1, textures);
    checkGLError("glGenTextures");
    textureId = textures[0];

    if (0 == textureId) {
        LOGE("~~~create Texture ID failed ~~~\n");
        return textureId;
    }

    unsigned char *image = NULL;
    int width, height, comp;
    image = SOIL_load_image(fileName, &width, &height, &comp, SOIL_LOAD_RGBA);

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

    return textureId;
}


GLboolean RenderUtil::loadMd2Model(const char *fileName, Md2* md2) {
    LOGD("~~~loadMd2Model()~~~\n");
}

GLuint RenderUtil::getFinalProgram() {
    LOGD("~~~getFinalProgram()~~~\n");
    return program;
}

GLuint RenderUtil::getFinalTexture() {
    LOGD("~~~getFinalTexture()~~~\n");
    return textureId;
}
