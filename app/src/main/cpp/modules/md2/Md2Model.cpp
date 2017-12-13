//
// Created by root on 17-10-25.
//

#include <md2/Md2Model.h>
#include <util/Debug.h>
#include <util/RenderUtil.h>
#include <matrix/MatrixState.h>

static int STEP = 5;

Md2Model::Md2Model():program(0), textureId(0),
                     mMMatrixHandle(0), mMVPMatrixHandle(0),
                     mCameraHandle(0), mLightHandle(0),
                     mPositionHandle(0), mNormalHandle(0),
                     mTextureCoordHandle(0), mColorHandle(0),
                     tx(0.0), ty(0.0), tz(0.0), rot(0.0),
                     sx(1.0), sy(1.0), sz(1.0), _md2(NULL) {

}

Md2Model::~Md2Model() {
    LOGD("~~~destoryModel()~~~\n");
    if (NULL != _md2){
        delete _md2;
    }
}


void Md2Model::initShader() {
    LOGD("~~~initShader()~~~\n");
    program = RenderUtil::createProgram("shader/vertextWithTexture.glsl", "shader/fragmentWithTexture.glsl");
}

void Md2Model::initModelData() {
    LOGD("~~~initModelData()~~~\n");
    bool reslut = RenderUtil::loadMd2Model("model/fish.md2",_md2);
    if (!reslut) {
        LOGE("~~~load model failed~~~\n");
    }
}

void Md2Model::initTextures() {
    LOGD("~~~initTextures()~~~\n");
    textureId = RenderUtil::createTexture("texture/bird.bmp");
}

void Md2Model::initHandle() {
    LOGD("~~~initHandle()~~~\n");
    mCameraHandle = (GLuint) glGetUniformLocation(program, "uCamera");
    mLightHandle = (GLuint) glGetUniformLocation(program, "uLightDirection");
    mMMatrixHandle = (GLuint) glGetUniformLocation(program, "uMMatrix");
    mMVPMatrixHandle = (GLuint) glGetUniformLocation(program, "uMVPMatrix");
    mPositionHandle = (GLuint) glGetAttribLocation(program, "aPosition");
    mNormalHandle = (GLuint) glGetAttribLocation(program, "aNormal");
    mTextureCoordHandle = (GLuint) glGetAttribLocation(program, "aTextureCoord");
}

void Md2Model::init() {
    LOGD("~~~init()~~~\n");
    initModelData();
    initShader();
    initTextures();
    initHandle();
}

void Md2Model::change() {
    LOGD("~~~change()~~~\n");
}

void Md2Model::updateMMatrix() {
    LOGD("~~~setMMatrix()~~~\n");
    MatrixState::rotate(rot, 1.0, 0.0, 0.0);
    rot = ((int) rot + STEP) % 360;
}

void Md2Model::draw() {
    LOGD("~~~draw()~~~\n");
    updateMMatrix();

    glUseProgram(program);
    glUniform3fv(mCameraHandle, 1, MatrixState::getCameraLocation());
    glUniform3fv(mLightHandle, 1, MatrixState::getLightLocation());
    glUniformMatrix4fv(mMMatrixHandle, 1, GL_FALSE, MatrixState::getMMatrix());
    glUniformMatrix4fv(mMVPMatrixHandle, 1, GL_FALSE, MatrixState::getFinalMVPMatrix());

    glEnableVertexAttribArray(mPositionHandle);
    //glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
    //                      COORDS_PER_VERTEX * sizeof(GLfloat), vertices);

    glEnableVertexAttribArray(mNormalHandle);
    //glVertexAttribPointer(mNormalHandle, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE,
    //                      COORDS_PER_VERTEX * sizeof(GLfloat), normals);

    glEnableVertexAttribArray(mTextureCoordHandle);
    //glVertexAttribPointer(mTextureCoordHandle, COORDS_PER_TEXTURES, GL_FLOAT, GL_FALSE,
    //                      COORDS_PER_TEXTURES * sizeof(GLfloat), textCoords);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);

    //glDrawElements(GL_TRIANGLES, sizeof(indexs) / sizeof(GLushort), GL_UNSIGNED_SHORT, indexs);

    glDisableVertexAttribArray(mPositionHandle);
    glDisableVertexAttribArray(mNormalHandle);
    glDisableVertexAttribArray(mTextureCoordHandle);
}