//
// Created by 70889 on 2017/9/27.
//

#include <stdio.h>
#include <malloc.h>
#include "FileUtil.h"
#include "Debug.h"

#ifdef __cplusplus
extern "C" {
#endif

AAssetManager *FileUtil::mgr = NULL;


void FileUtil::setAAssetManager(AAssetManager *manager) {
    LOGD("~~~setAAssetManager()~~~\n");
    mgr = manager;
}

char *FileUtil::read(const char *fileName) {
    LOGD("~~~read()~~~\n");
    LOGI("~~~fileName = %s~~~\n", fileName);
    if (NULL == mgr) {
        return NULL;
    }
    AAsset *asset = openFromAsset(fileName);
    char *data = readFromAsset(asset);
    closeFromAsset(asset);
    return data;
}

AAsset *FileUtil::openFromAsset(const char *fileName) {
    LOGD("~~~openFromAsset()~~~\n");
    LOGI("~~~fileName = %s~~~\n", fileName);
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    return asset;
}

char *FileUtil::readFromAsset(AAsset *asset) {
    LOGD("~~~readFromAsset()~~~\n");
    if (NULL == asset) {
        LOGE("~~~open asset file failed!~~~\n");
        return NULL;
    }
    off_t bufferSize = AAsset_getLength(asset);
    char *data = (char *) malloc(sizeof(char) * (bufferSize + 1));
    data[bufferSize] = '\0';
    int size = AAsset_read(asset, (void *) data, (size_t) bufferSize);
    return data;
}

void FileUtil::closeFromAsset(AAsset *asset) {
    LOGD("~~~closeFromAsset()~~~\n");
    AAsset_close(asset);
}

int FileUtil::getBufferFromAsset(void *buffer, const char *fileName) {
    LOGD("~~~getBufferFromAsset()~~~\n");
    LOGI("~~~fileName = %s~~~\n", fileName);
    if (NULL == mgr) {
        return -1;
    }

    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    off_t bufferSize = AAsset_getLength(asset);

    int size = AAsset_read(asset, buffer, (size_t) bufferSize);
    AAsset_close(asset);
    return size;
}


off_t FileUtil::getFileSize(const char *fileName) {
    LOGD("~~~getFileSize()~~~\n");
    LOGI("~~~fileName = %s~~~\n", fileName);
    if (NULL == mgr) {
        return 0;
    }
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    if (NULL == asset) {
        LOGE(" %s", "asset==NULL");
        return EOF;
    }
    off_t size = AAsset_getLength(asset);
    AAsset_close(asset);
    return size;
}


#ifdef __cplusplus
}
#endif