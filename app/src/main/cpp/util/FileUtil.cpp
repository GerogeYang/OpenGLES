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

char *FileUtil::getStrFromAsset(const char *fileName) {
    LOGD("~~~getStrFromAsset()~~~\n");
    LOGI("~~~fileName = %s~~~\n", fileName);
    if (NULL == mgr) {
        return NULL;
    }
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    off_t bufferSize = AAsset_getLength(asset);
    char *data = (char *) malloc(sizeof(char) * (bufferSize + 1));
    data[bufferSize] = '\0';
    int size = AAsset_read(asset, (void *) data, (size_t) bufferSize);
    return data;
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
    return size;
}


off_t FileUtil::getFileSize(const char *fileName) {
    LOGD("~~~getFileSize()~~~\n");
    LOGI("~~~fileName = %s~~~\n", fileName);
    if (NULL == mgr) {
        return 0;
    }
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    if (asset == NULL) {
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