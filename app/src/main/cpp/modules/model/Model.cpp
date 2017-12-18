//
// Created by root on 17-12-14.
//

#include <model/Model.h>
#include <util/Debug.h>
#include <util/FileUtil.h>

Model::Model():assimpLoader(NULL) {

}

Model::~Model() {
    LOGD("~~~destoryModel()~~~\n");
    if (assimpLoader) {
        delete assimpLoader;
    }
}

void Model::init() {
    LOGD("~~~initModelData()~~~\n");
    assimpLoader = new AssimpLoader();

    std::string modeFilname;
    std::string mtlFilename;
    std::string texFilename;

    bool isFilesPresent  =
            FileUtil::extractAssetReturnFilename("amenemhat/amenemhat.obj", modeFilname) &&
            FileUtil::extractAssetReturnFilename("amenemhat/amenemhat.mtl", mtlFilename) &&
            FileUtil::extractAssetReturnFilename("amenemhat/amenemhat.jpg", texFilename);
    if( !isFilesPresent ) {
        LOGE("Model %s does not exist!", modeFilname.c_str());
        return;
    }
    assimpLoader->Load3DModel(modeFilname);
}

void Model::change() {
    LOGD("~~~change()~~~\n");
}

void Model::updateMMatrix() {
    LOGD("~~~updateMMatrix()~~~\n");
}

void Model::draw() {
    LOGD("~~~draw()~~~\n");
    updateMMatrix();
    assimpLoader->Render3DModel();
}
