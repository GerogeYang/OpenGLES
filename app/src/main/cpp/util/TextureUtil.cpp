//
// Created by root on 17-10-12.
//

#include <stdio.h>
#include <setjmp.h>
#include <malloc.h>
#include "TextureUtil.h"
#include "Debug.h"
#include "../libpng/png.h"

gl_texture_t *TextureUtil::texinfo = NULL;

void TextureUtil::checkGLError(const char *op) {
    LOGD("~~~checkGLError()~~~\n");
    for (GLint error = glGetError(); error; error = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

void TextureUtil::getPNGtextureInfo(int color_type, gl_texture_t *texinfo) {
    LOGD("~~~getPNGtextureInfos()~~~\n");
    switch (color_type) {
        case PNG_COLOR_TYPE_GRAY:
            texinfo->format = GL_LUMINANCE;
            texinfo->internalFormat = 1;
            break;

        case PNG_COLOR_TYPE_GRAY_ALPHA:
            texinfo->format = GL_LUMINANCE_ALPHA;
            texinfo->internalFormat = 2;
            break;

        case PNG_COLOR_TYPE_RGB:
            texinfo->format = GL_RGB;
            texinfo->internalFormat = 3;
            break;

        case PNG_COLOR_TYPE_RGB_ALPHA:
            texinfo->format = GL_RGBA;
            texinfo->internalFormat = 4;
            break;

        default:
            LOGE("error: get PNG valid texture infos\n");
            break;
    }
}

gl_texture_t *TextureUtil::getPNGFromAsset(const char *pngFileName) {
    LOGD("~~~getPNGFromAsset()~~~\n");
    FILE *fp = NULL;
    png_byte magic[8];
    png_structp png_ptr;
    png_infop info_ptr;
    int bit_depth, color_type;
    png_bytep *row_pointers = NULL;
    png_uint_32 w, h;
    int i;
    /* Open image file */
    fp = fopen(pngFileName, "rb");
    if (!fp) {
        LOGE("error: couldn't open \"%s\"!\n", pngFileName);
        return NULL;
    }
    /* Read magic number */
    fread(magic, 1, sizeof(magic), fp);
    /* Check for valid magic number */
    if (!png_check_sig (magic, sizeof(magic))) {
        LOGE("error: \"%s\" is not a valid PNG image!\n", pngFileName);
        fclose(fp);
        return NULL;
    }
    /* Create a png read struct */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        LOGE("error: create PNG image read_struct failed !\n");
        fclose(fp);
        return NULL;
    }
    /* Create a png info struct */
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        LOGE("error: create PNG image info_ptr failed !\n");
        fclose(fp);
        png_destroy_read_struct(&png_ptr, NULL, NULL);
        return NULL;
    }

    /* Create our OpenGL texture object */
    texinfo = (gl_texture_t *) malloc(sizeof(gl_texture_t));
    /* Initialize the setjmp for returning properly after a libpng error occured */
    if (setjmp(png_jmpbuf(png_ptr))) {
        LOGE("error: initialize the setjmp failed !\n");
        fclose(fp);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        if (texinfo) {
            if (texinfo->texels) {
                free(texinfo->texels);
            }
            free(texinfo);
        }
        return NULL;
    }
    /* Setup libpng for using standard C fread() function with our FILE pointer */
    png_init_io(png_ptr, fp);
    /* Tell libpng that we have already read the magic number */
    png_set_sig_bytes(png_ptr, sizeof(magic));
    /* Read png info */
    png_read_info(png_ptr, info_ptr);
    /* Get some usefull information from header */
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    /* Convert index color images to RGB images */
    if (color_type == PNG_COLOR_TYPE_PALETTE) {
        png_set_palette_to_rgb(png_ptr);
    }
    /* Convert 1-2-4 bits grayscale images to 8 bits grayscale. */
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8) {
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    }

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS)) {
        png_set_tRNS_to_alpha(png_ptr);
    }

    if (bit_depth == 16) {
        png_set_strip_16(png_ptr);
    } else if (bit_depth < 8) {
        png_set_packing(png_ptr);
    }

    /* Update info structure to apply transformations */
    png_read_update_info(png_ptr, info_ptr);
    /* Retrieve updated information */
    png_get_IHDR(png_ptr, info_ptr, &w, &h, &bit_depth, &color_type, NULL, NULL, NULL);
    texinfo->width = (GLsizei) w;
    texinfo->height = (GLsizei) h;
    /* Get image format  and components per pixel */
    getPNGtextureInfo(color_type, texinfo);
    /* We can now allocate memory for storing pixel data */
    texinfo->texels = (GLubyte *) malloc(
            sizeof(GLubyte) * texinfo->width * texinfo->height * texinfo->internalFormat);
    /* Setup a pointer array. Each one points at the begening of a row. */
    row_pointers = (png_bytep *) malloc(sizeof(png_bytep) * texinfo->height);
    for (i = 0; i < texinfo->height; ++i) {
        row_pointers[i] = (png_bytep) (texinfo->texels +
                                       ((texinfo->height - (i + 1)) * texinfo->width *
                                        texinfo->internalFormat));
    }
    /* Read pixel data using row pointers */
    png_read_image(png_ptr, row_pointers);
    /* Finish decompression and release memory */
    png_read_end(png_ptr, NULL);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    /* We don't need row pointers anymore */
    free(row_pointers);
    fclose(fp);
    return texinfo;
}

gl_texture_t *TextureUtil::getOtherImangeFromAsset(const char *imageFileName) {
    FILE *fp = NULL;
    unsigned char *texels;
    unsigned long len = 0;
    unsigned long width = 0;
    unsigned long height = 0;

    fp = fopen(imageFileName, "rb");
    if (!fp) {
        LOGE("error: couldn't open \"%s\"!\n", imageFileName);
        return NULL;
    }

    fseek(fp, 18, SEEK_SET);
    fread(&width, 4, 1, fp);
    fread(&height, 4, 1, fp);
    fseek(fp, 0, SEEK_END);
    len = (unsigned long) (ftell(fp) - 54);
    texels = (unsigned char *) malloc(len);
    fseek(fp, 54, SEEK_SET);
    fread(texels, len, 1, fp);
    fclose(fp);

    texinfo->width = (GLsizei) width;
    texinfo->height = (GLsizei) height;
    texinfo->internalFormat = 3;
    texinfo->format = GL_RGB;
    texinfo->texels = texels;
}

GLuint TextureUtil::loadTextures(const char *fileName) {
    LOGD("~~~loadTextrues()~~~\n");
    GLuint *textures = new GLuint[1];
    glGenTextures(1, textures);
    checkGLError("glGenTextures");
    GLuint textureId = textures[0];

    if (!strcmp(fileName,"png")){
        texinfo = getPNGFromAsset(fileName);
    } else {
        texinfo = getOtherImangeFromAsset(fileName);
    }

    if ((0 != textureId) && (NULL != texinfo)) {
        glBindTexture(GL_TEXTURE_2D, textureId);
        checkGLError("glBindTexture");
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        checkGLError("glTexParameterf");
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        checkGLError("glTexParameterf");
        glTexImage2D(GL_TEXTURE_2D, 0, texinfo->internalFormat, texinfo->width, texinfo->height, 0, texinfo->format, GL_UNSIGNED_BYTE, texinfo->texels);
        destoryTextureInfos();
    }
    return textureId;
}

void TextureUtil::destoryTextureInfos() {
    LOGD("~~~destoryTextures()~~~\n");
    if (NULL != texinfo){
        if (NULL != texinfo->texels){
            free(texinfo->texels);
        }
        free(texinfo);
    }
}