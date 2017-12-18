//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_FILEUTIL_H
#define OPENGLES_FILEUTIL_H

#include <android/asset_manager_jni.h>
#include <android/asset_manager.h>
#include <string>

class FileUtil {
private:
    static AAssetManager *mgr;

    static std::string apkInternalPath;

public:
    static void init(AAssetManager *manager, std::string path);

    static char *readFromAsset(std::string fileName);

    static bool extractAssetReturnFilename(std::string assetFilename, std::string &fileName, bool checkIfFileIsAvailable = false);

    static std::string getFileName(std::string fileName);

    static std::string getDirectoryName(std::string fullFileName);

};


#endif //OPENGLES_FILEUTIL_H
