//
// Created by 7088"ES" on 2017/"ES"/22.
//

#include <Render.h>
#include <util/Debug.h>
#include <util/RenderUtil.h>
#include <matrix/MatrixState.h>
#include <util/FileUtil.h>

#ifdef __cplusplus
extern "C" {
#endif


Render::Render() : _triangle(NULL), _square(NULL), _cubeWithLight(NULL),
                   _triangleWithTexture(NULL),_md2model(NULL),_model(NULL) {
/*    _triangle = new Triangle();
    _square = new Square();
    _cubeWithLight = new CubeWithLight();*/
    _triangleWithTexture = new TriangleWithTexture();
    /*_md2model = new Md2Model();*/
    _model = new Model();
}

Render::~Render() {
    LOGD("~~~destoryRender()~~~\n");
    MatrixState::destoryMatrixState();
    if (NULL != _triangle) {
        delete _triangle;
        _triangle = NULL;
    }

    if (NULL != _square) {
        delete _square;
        _square = NULL;
    }

    if (NULL != _cubeWithLight) {
        delete _cubeWithLight;
        _cubeWithLight = NULL;
    }

    if (NULL != _triangleWithTexture) {
        delete _triangleWithTexture;
        _triangleWithTexture = NULL;
    }

    if (NULL != _md2model) {
        delete _md2model;
        _md2model = NULL;
    }

    if (NULL != _model) {
        delete _model;
        _model = NULL;
    }
}

void Render::printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

void Render::init() {
    LOGD("~~~init()~~~\n");
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    MatrixState::init();
    MatrixState::setLightLocation(30.0f, 50.0f, 500.0f);
/*    _triangle->init();
    _square->init();
    _cubeWithLight->init();*/
    _triangleWithTexture->init();
/*    _md2model->init();*/
    _model->init();
}

void Render::createEs(JNIEnv *env, jobject assetManager, jstring pathToInternalDir) {
    LOGD("~~~createEs()~~~\n");
    AAssetManager *aamIn = AAssetManager_fromJava(env, assetManager);

    const char *cPathToInternalDir;
    std::string apkInternalPath;
    cPathToInternalDir = env->GetStringUTFChars(pathToInternalDir, NULL);
    apkInternalPath = std::string(cPathToInternalDir);
    env->ReleaseStringUTFChars(pathToInternalDir, cPathToInternalDir);

    FileUtil::init(aamIn, apkInternalPath);
    init();
}

void Render::changeEs(int width, int height) {
    LOGD("~~~changeEs()~~~\n");
    glViewport(0, 0, width, height);
    float ratio = (float) width / height;
    MatrixState::setProjectFrustum(-ratio, ratio, -1, 1, 3, 500);
    MatrixState::setCamera(5.0f, 5.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
/*    _triangle->change();
    _square->change();
    _cubeWithLight->change();*/
    _triangleWithTexture->change();
/*    _md2model->change();*/
    _model->change();
}

void Render::drawEs() {
    LOGD("~~~drawEs()~~~\n");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
/*    _triangle->draw();
    _square->draw();
    MatrixState::pushMatrix();
    MatrixState::translate(-1.5f, 0.0, 0.0);
    _cubeWithLight->draw();
    MatrixState::popMatrix();*/
    MatrixState::pushMatrix();
    MatrixState::translate(-1.5f, 0.0, 0.0);
    _triangleWithTexture->draw();
    MatrixState::popMatrix();
/*    MatrixState::pushMatrix();
    _md2model->draw();
    MatrixState::popMatrix();*/
    MatrixState::pushMatrix();
    MatrixState::translate(1.5f, 0.0, 0.0);
    _model->draw();
    MatrixState::popMatrix();
}


#ifdef __cplusplus
}
#endif