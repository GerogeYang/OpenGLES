//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_BASESHAPE_H
#define OPENGLES_BASESHAPE_H


class BaseShape {
private:
    virtual void init();

public:
    BaseShape();

    virtual ~BaseShape();

    virtual void draw();
};


#endif //OPENGLES_BASESHAPE_H
