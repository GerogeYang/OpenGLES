//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_FILEUTIL_H
#define OPENGLES_FILEUTIL_H

#include <android/asset_manager.h>
#include <jni.h>

char *getStrFromFile(const char *fileName);

class FileUtil {
private:
    static AAssetManager *mgr;

public:
    static void setAAssetManager(AAssetManager *manager);

    static off_t getFileSize(const char *fileName);

    static char* getStrFromAsset(const char *fileName);

};


#endif //OPENGLES_FILEUTIL_H
