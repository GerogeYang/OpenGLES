//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_FILEUTIL_H
#define OPENGLES_FILEUTIL_H

#include <jni.h>
#include <android/asset_manager.h>
#include <GLES2/gl2.h>

typedef struct{
    GLsizei width;
    GLsizei height;
    GLenum format;
    GLint internalFormat;
    GLuint id;
    GLubyte *texels;
}gl_texture_t;

class FileUtil {
private:
    static AAssetManager *mgr;

    static gl_texture_t *texinfo;

    static void getPNGtextureInfo(int color_type,  gl_texture_t *texinfo);

public:
    static void setAAssetManager(AAssetManager *manager);

    static char* getStrFromAsset(const char *fileName);

    static gl_texture_t *getPNGFromAsset(const char *pngFileName);

    static gl_texture_t *getOtherImangeFromAsset(const char *imageFileName);

    static char *getStrFromFile(const char *fileName);

    static off_t getFileSize(const char *fileName);

};


#endif //OPENGLES_FILEUTIL_H
