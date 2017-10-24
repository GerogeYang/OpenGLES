//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_FILEUTIL_H
#define OPENGLES_FILEUTIL_H

#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>

class FileUtil {
private:
    static AAssetManager *mgr;

public:
    static void setAAssetManager(AAssetManager *manager);

    static char *read(const char *fileName);

    static AAsset *openFromAsset(const char *fileName);

    static char *readFromAsset(AAsset *asset);

    static void closeFromAsset(AAsset *asset);

    static int getBufferFromAsset(void *buffer, const char *fileName);

    static off_t getFileSize(const char *fileName);

};


#endif //OPENGLES_FILEUTIL_H
