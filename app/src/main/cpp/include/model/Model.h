//
// Created by root on 17-12-14.
//

#ifndef OPENGLES_MODEL_H
#define OPENGLES_MODEL_H

#include "AssimpLoader.h"

class Model{
private:
    static const int COORDS_PER_VERTEX = 3;

    static const int COORDS_PER_COLORS = 4;

    static const int COORDS_PER_TEXTURES = 2;

    GLuint program;

    AssimpLoader *assimpLoader;

    void updateMMatrix();

public:
    Model();

    ~Model();

    void init();

    void change();

    void draw();

};

#endif //OPENGLES_MODEL_H
