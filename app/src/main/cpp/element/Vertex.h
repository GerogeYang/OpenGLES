//
// Created by 70889 on 2017/9/22.
//

#ifndef OPENGLES_VERTEX3D_H
#define OPENGLES_VERTEX3D_H

#ifndef OPENGLES_GL_H
#define OPENGLES_GL_H

#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#endif //OPENGLES_GL_H

typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vertex3D;

class Vertex {
private:
public:
    static void vertex3DSet(Vertex3D *vertex, GLfloat x, GLfloat y, GLfloat z);
};


#endif //OPENGLES_VERTEX3D_H
