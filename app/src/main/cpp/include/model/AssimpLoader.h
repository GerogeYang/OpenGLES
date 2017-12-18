//
// Created by root on 17-12-14.
//

#ifndef OPENGLES_ASSIMPLOADER_H
#define OPENGLES_ASSIMPLOADER_H

#include <assimp/scene.h>
#include <GLES2/gl2.h>
#include <assimp/Importer.hpp>
#include <map>

// info used to render a mesh
struct MeshInfo {
    GLuint  textureIndex;
    int     numberOfFaces;
    GLuint  faceBuffer;
    GLuint  vertexBuffer;
    GLuint  textureCoordBuffer;
};

class AssimpLoader{
private:
    static const int COORDS_PER_VERTEX = 3;

    static const int COORDS_PER_COLORS = 4;

    static const int COORDS_PER_TEXTURES = 2;

    std::vector<struct MeshInfo> modelMeshes;

    Assimp::Importer *importer;

    const aiScene* scene;

    std::map<std::string, GLuint> textureNameMap;

    bool isObjectLoaded;

    GLuint  program;

    GLuint mMMatrixHandle;

    GLuint mMVPMatrixHandle;

    GLuint mCameraHandle;

    GLuint mLightHandle;

    GLuint mPositionHandle;

    GLuint mNormalHandle;

    GLuint mColorHandle;

    GLuint mTextureIdHandle;

    GLuint mTextureCoordHandle;

    void initshader();

    void initHandle();

    void parseModel();

    bool LoadTextures(std::string modelFilename);

public:
    AssimpLoader();

    ~AssimpLoader();

    bool Load3DModel(std::string modelFilename);

    bool LoadModelMtl(std::string mtlFilename);

    void Render3DModel();

    void Delete3DModel();

};

#endif //OPENGLES_ASSIMPLOADER_H
