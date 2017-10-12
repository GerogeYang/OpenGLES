//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_BASESHAPE_H
#define OPENGLES_BASESHAPE_H


#include <GLES2/gl2.h>

class BaseShape {
private:
    virtual void setMMatrix();

public:
    BaseShape();

    virtual ~BaseShape();

    virtual void init();

    virtual void change();

    virtual void draw();

};


#endif //OPENGLES_BASESHAPE_H