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
    LOGD("~~~setAAssetManager()~~~");
    mgr = manager;
}


char* FileUtil::getStrFromAsset(const char *fileName) {
    LOGD("~~~getAssetStr()~~~");
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    off_t bufferSize = AAsset_getLength(asset);
    char* data = (char*) malloc(sizeof(char)*(bufferSize + 1));
    data[bufferSize] = '\0';
    int size = AAsset_read(asset, (void*)data, (size_t)bufferSize);
    return data;
}

off_t FileUtil::getFileSize(const char *fileName) {
    LOGD("~~~getFileSize()~~~");
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    if (asset == NULL) {
        LOGE(" %s", "asset==NULL");
        return EOF;
    }
    off_t size = AAsset_getLength(asset);
    AAsset_close(asset);

    return size;
}

char* FileUtil::getStrFromFile(const char *fileName) {
    LOGD("~~~getStrFromeFile()~~~");
    FILE *pFile = fopen(fileName, "r");
    char *pBuf;
    fseek(pFile, 0, SEEK_END);
    long len = ftell(pFile);
    pBuf = (char*) malloc(sizeof(char)*(len + 1));;
    rewind(pFile);
    fread(pBuf, 1, (size_t)len, pFile);
    pBuf[len] = 0;
    fclose(pFile);
    return pBuf;
}

#ifdef __cplusplus
}
#endif