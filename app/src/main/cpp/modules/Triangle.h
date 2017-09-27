//
// Created by 70889 on 2017/9/22.
//

#ifndef OPENGLES_TRIANGLE_H
#define OPENGLES_TRIANGLE_H

#include <GLES2/gl2.h>
#include "BaseShape.h"

class Triangle : public BaseShape {
private:

public:
    Triangle();

    ~Triangle();

    void init();

    void draw();
};


#endif //OPENGLES_TRIANGLE_H
