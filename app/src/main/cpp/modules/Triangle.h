//
// Created by 70889 on 2017/9/22.
//

#ifndef OPENGLES_TRIANGLE_H
#define OPENGLES_TRIANGLE_H

#include "BaseShape.h"

class Triangle : public BaseShape {
private:
    void init();

public:
    Triangle();

    ~Triangle();

    void draw();
};


#endif //OPENGLES_TRIANGLE_H
