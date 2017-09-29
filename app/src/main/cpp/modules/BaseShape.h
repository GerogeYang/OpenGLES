//
// Created by 70889 on 2017/9/27.
//

#ifndef OPENGLES_BASESHAPE_H
#define OPENGLES_BASESHAPE_H


class BaseShape {
private:

public:
    BaseShape();

    virtual ~BaseShape();

    virtual void init();

    virtual void change(int width, int height);

    virtual void draw();
};


#endif //OPENGLES_BASESHAPE_H
