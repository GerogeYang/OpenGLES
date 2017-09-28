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

AAssetManager *FileUtil::mgr;

/*char *getStr(const char *fileName) {
    LOGD("~~~getStr()~~~");
    FILE *pFile = fopen(fileName, "r"); //获取文件的指针
    char *pBuf;  //定义文件指针
    fseek(pFile, 0, SEEK_END); //把指针移动到文件的结尾 ，获取文件长度
    int len = ftell(pFile); //获取文件长度
    pBuf = new char[len + 1]; //定义数组长度
    rewind(pFile); //把指针移动到文件开头 因为我们一开始把指针移动到结尾，如果不移动回来 会出错
    fread(pBuf, 1, len, pFile); //读文件
    pBuf[len] = 0; //把读到的文件最后一位 写为0 要不然系统会一直寻找到0后才结束
    fclose(pFile); // 关闭文件
    return pBuf;
}*/

void FileUtil::setAAssetManager(AAssetManager *manager) {
    LOGD("~~~setAAssetManager()~~~");
    mgr = manager;
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

char* FileUtil::getStrFromAsset(const char *fileName) {
    LOGD("~~~getAssetStr()~~~");
    LOGI("mgr = %s, fileName = %s\n",mgr,fileName);
    AAsset *asset = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
    off_t bufferSize = AAsset_getLength(asset);
    char* data = (char*) malloc(bufferSize + 1);
    data[bufferSize] = '\0';
    int size = AAsset_read(asset, (void*)data, bufferSize);
    return data;
}

#ifdef __cplusplus
}
#endif