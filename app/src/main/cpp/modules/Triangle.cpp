//
// Created by 70889 on 2017/9/22.
//

#include <GLES/gl.h>
#include "Triangle.h"
#include "../util/Debug.h"

GLfloat gVertexts[] ={
        0.0f,1.0f,-3.0f,
        1.0f,0.0f,-3.0f,
        -1.0f,0.0f,-3.0f
};

Triangle::Triangle() {

}

Triangle::~Triangle() {

}

void Triangle::init() {
    LOGD("~~~init()~~~");
}

void Triangle::draw() {
    LOGD("~~~draw()~~~");
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0,0.0,0.0,1.0);
    glVertexPointer(3,GL_FLOAT,0,gVertexts);
    glDrawArrays(GL_TRIANGLES, 0, 9);
    glDisableClientState(GL_VERTEX_ARRAY);
}