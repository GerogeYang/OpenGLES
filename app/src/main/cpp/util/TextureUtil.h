//
// Created by root on 17-10-12.
//

#ifndef OPENGLES_TEXTUREUTIL_H
#define OPENGLES_TEXTUREUTIL_H


#include <GLES2/gl2.h>

typedef struct{
    GLsizei width;
    GLsizei height;
    GLenum format;
    GLint internalFormat;
    GLuint id;
    GLubyte *texels;
}gl_texture_t;

class TextureUtil {
private:
    static gl_texture_t *texinfo;

    static void checkGLError(const char *op);

    static void getPNGtextureInfo(int color_type,  gl_texture_t *texinfo);

    static gl_texture_t *getPNGFromAsset(const char *pngFileName);

    static gl_texture_t *getOtherImangeFromAsset(const char *imageFileName);

    static void destoryTextureInfos();

public:
    static GLuint loadTextures(const char *fileName);



};


#endif //OPENGLES_TEXTUREUTIL_H
