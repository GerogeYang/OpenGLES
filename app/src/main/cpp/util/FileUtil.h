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

    static char *getStrFromAsset(const char *fileName);

    static int getBufferFromAsset(void *buffer, const char *fileName);

    static off_t getFileSize(const char *fileName);

};


#endif //OPENGLES_FILEUTIL_H
