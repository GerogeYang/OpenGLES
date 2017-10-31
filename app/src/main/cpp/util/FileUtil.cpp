//
// Created by 70889 on 2017/9/27.
//

#include <stdio.h>
#include <malloc.h>
#include <Debug.h>
#include <util/FileUtil.h>


#ifdef __cplusplus
extern "C" {
#endif

AAssetManager *FileUtil::mgr = NULL;


void FileUtil::init(AAssetManager *manager) {
    LOGD("~~~setAAssetManager()~~~\n");
    mgr = manager;
}

char *FileUtil::readFromAsset(const char *fileName) {
    LOGD("~~~readFromAsset()~~~\n");
    LOGI("~~~fileName = %s~~~\n", fileName);
    if (NULL == mgr) {
        return NULL;
    }
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    if (NULL == asset) {
        LOGE("~~~open asset file failed!~~~\n");
        return NULL;
    }
    off_t bufferSize = AAsset_getLength(asset);
    char *data = (char *) malloc(sizeof(char) * (bufferSize + 1));
    data[bufferSize] = '\0';
    int size = AAsset_read(asset, (void *) data, (size_t) bufferSize);
    AAsset_close(asset);
    return data;
}

#ifdef __cplusplus
}
#endif