//
// Created by 70889 on 2017/9/27.
//

#include <stdio.h>
#include <malloc.h>
#include <Debug.h>
#include <pthread.h>
#include <string>
#include <FileUtil.h>
#include <SOIL.h>


AAssetManager *FileUtil::mgr = NULL;
std::string FileUtil::apkInternalPath;

#ifdef __cplusplus
extern "C" {
#endif

void FileUtil::init(AAssetManager *manager, std::string path) {
    LOGD("~~~init()~~~\n");
    mgr = manager;
    apkInternalPath = path;
    SOIL_init(mgr);
}

char *FileUtil::readFromAsset(std::string fileName) {
    LOGD("~~~readFromAsset()~~~\n");
    LOGI("~~~fileName = %s~~~\n", fileName.c_str());
    if (NULL == mgr) {
        return NULL;
    }
    AAsset *asset = AAssetManager_open(mgr, fileName.c_str(), AASSET_MODE_UNKNOWN);
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

bool FileUtil::extractAssetReturnFilename(std::string assetFilename, std::string &fileName,
                                          bool checkIfFileIsAvailable) {
    LOGD("~~~extractAssetReturnFilename()~~~\n");
    // construct the filename in internal storage by concatenating with path to internal storage
    fileName = apkInternalPath + "/" + getFileName(assetFilename);

    LOGI("~~~fileName = %s~~~\n", fileName.c_str());

    // check if the file was previously extracted and is available in app's internal dir
    FILE* file = fopen(fileName.c_str(), "rb");
    if (file && checkIfFileIsAvailable) {

        LOGI("Found extracted file in assets: %s", fileName.c_str());
        fclose(file);
        return true;
    }

    // let us look for the file in assets
    bool result = false;

    // AAsset objects are not thread safe and need to be protected with mutex

    // Open file
    AAsset* asset = AAssetManager_open(mgr, assetFilename.c_str(), AASSET_MODE_STREAMING);

    char buf[BUFSIZ];
    int nb_read = 0;
    if (asset != NULL)
    {
        FILE* out = fopen(fileName.c_str(), "w");
        while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0)
        {
            fwrite(buf, nb_read, 1, out);
        }
        fclose(out);
        AAsset_close(asset);
        result = true;

        LOGI("Asset extracted: %s", fileName.c_str());
    }
    else
    {
        LOGE("Asset not found: %s", assetFilename.c_str());
    }

    return result;
}

std::string FileUtil::getFileName(std::string fileName) {
    LOGD("~~~getFileName()~~~\n");
    // assume filename is of the form "<path>/<name>.<type>"
    std::string::size_type slashIndex = fileName.find_last_of("/");

    std::string onlyName;
    if (slashIndex == std::string::npos) {
        onlyName = fileName.substr(0, std::string::npos);
    } else {
        onlyName = fileName.substr(slashIndex + 1, std::string::npos);
    }

    return onlyName;
}

std::string FileUtil::getDirectoryName(std::string fullFileName) {

    std::string::size_type slashIndex = fullFileName.find_last_of("/");
    std::string directoryName;
    if (slashIndex == std::string::npos) {
        directoryName = ".";
    } else if (slashIndex == 0) {
        directoryName = "/";
    } else {
        directoryName = fullFileName.substr(0, slashIndex);
    }
    return directoryName;
}


#ifdef __cplusplus
}
#endif