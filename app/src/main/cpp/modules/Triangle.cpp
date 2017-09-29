//
// Created by 70889 on 2017/9/22.
//

#include <GLES/gl.h>
#include <malloc.h>
#include "Triangle.h"
#include "../util/Debug.h"
#include "../util/FileUtil.h"
#include "../util/RenderUtil.h"


static GLfloat vertices[] = {
        0.5f,  0.5f, 0.0f, // top
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f  // bottom right
};

GLfloat colors[] = { 1.0f, 1.0f, 1.0f, 1.0f };

Triangle::Triangle():vertexShaderCode(NULL),fragmentShaderCode(NULL),mPositionHandle(0),mColorHandle(0),mMatrixHandle(0) {

}

Triangle::~Triangle() {
    LOGD("~~~~DestoryTriangle()~~~~~~\n");
    if (NULL != vertexShaderCode) {
        free(vertexShaderCode);
        vertexShaderCode = NULL;
    }

    if (NULL != fragmentShaderCode) {
        free(fragmentShaderCode);
        fragmentShaderCode = NULL;
    }
}

void Triangle::init() {
    LOGD("~~~init()~~~");
    vertexShaderCode = FileUtil::getStrFromAsset("vertextSource.glsl");
    fragmentShaderCode = FileUtil::getStrFromAsset("fragmentSource.glsl");
    program = RenderUtil::createProgram(vertexShaderCode, fragmentShaderCode);
}

void Triangle::change() {

}

void Triangle::draw() {
    LOGD("~~~draw()~~~");
    glUseProgram(program);
    mMatrixHandle= glGetUniformLocation(program,"vMatrix");
    glUniformMatrix4fv(mMatrixHandle,1,false,mMVPMatrix,0);

    mPositionHandle = (GLuint) glGetAttribLocation(program, "vPosition");
    glEnableVertexAttribArray(mPositionHandle);
    glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, COORDS_PER_VERTEX* sizeof(GLfloat), vertices);
    mColorHandle = (GLuint) glGetUniformLocation(program, "vColor");
    glUniform4fv(mColorHandle, 8, colors);
    glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices)/COORDS_PER_VERTEX);
    glDisableVertexAttribArray(mPositionHandle);
}