//
// Created by root on 17-12-14.
//

#include <model/AssimpLoader.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <util/Debug.h>
#include <util/FileUtil.h>
#include <util/RenderUtil.h>
#include <matrix/MatrixState.h>
#include <opencv2/opencv.hpp>

AssimpLoader::AssimpLoader() {
    importer = new Assimp::Importer;
    scene = NULL;
    initshader();
    initHandle();
}

AssimpLoader::~AssimpLoader() {
    LOGD("~~~destoryAssimpLoader()~~~\n");
    Delete3DModel();
    if(importer) {
        delete importer;
        importer = NULL;
    }
    scene = NULL; // gets deleted along with importerPtr
}

void AssimpLoader::initshader() {
    LOGD("~~~initshader()~~~\n");
    program = RenderUtil::createProgram("shader/modelTextured.vsh", "shader/modelTextured.fsh");
}


void AssimpLoader::initHandle() {
    LOGD("~~~initHandle()~~~\n");
    mPositionHandle     = (GLuint)glGetAttribLocation(program, "aPosition");
    mTextureCoordHandle = (GLuint)glGetAttribLocation(program, "aTextureCoord");
    mMVPMatrixHandle    = (GLuint)glGetUniformLocation(program, "uMVPMatrix");
    mTextureIdHandle    = (GLuint)glGetUniformLocation(program, "sTexture");
}

void AssimpLoader::parseModel() {
    LOGD("~~~parseModel()~~~\n");
    struct MeshInfo newMeshInfo; // this struct is updated for each mesh in the model
    GLuint buffer;

    // For every mesh -- load face indices, vertex positions, vertex texture coords
    // also copy texture index for mesh into newMeshInfo.textureIndex
    for (unsigned int n = 0; n < scene->mNumMeshes; ++n) {

        const aiMesh *mesh = scene->mMeshes[n]; // read the n-th mesh

        // create array with faces
        // convert from Assimp's format to array for GLES
        unsigned int *faceArray = new unsigned int[mesh->mNumFaces * 3];
        unsigned int faceIndex = 0;
        for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {

            // read a face from assimp's mesh and copy it into faceArray
            const aiFace *face = &mesh->mFaces[t];
            memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
            faceIndex += 3;

        }
        newMeshInfo.numberOfFaces = scene->mMeshes[n]->mNumFaces;

        // buffer for faces
        if (newMeshInfo.numberOfFaces) {

            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                         sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray,
                         GL_STATIC_DRAW);
            newMeshInfo.faceBuffer = buffer;

        }
        delete[] faceArray;

        // buffer for vertex positions
        if (mesh->HasPositions()) {

            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(float) * 3 * mesh->mNumVertices, mesh->mVertices,
                         GL_STATIC_DRAW);
            newMeshInfo.vertexBuffer = buffer;

        }

        // buffer for vertex texture coordinates
        // ***ASSUMPTION*** -- handle only one texture for each mesh
        if (mesh->HasTextureCoords(0)) {

            float * textureCoords = new float[2 * mesh->mNumVertices];
            for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {
                textureCoords[k * 2] = mesh->mTextureCoords[0][k].x;
                textureCoords[k * 2 + 1] = mesh->mTextureCoords[0][k].y;
            }
            glGenBuffers(1, &buffer);
            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferData(GL_ARRAY_BUFFER,
                         sizeof(float) * 2 * mesh->mNumVertices, textureCoords,
                         GL_STATIC_DRAW);
            newMeshInfo.textureCoordBuffer = buffer;
            delete[] textureCoords;

        }

        // unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // copy texture index (= texture name in GL) for the mesh from textureNameMap
        aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];
        aiString texturePath;	//contains filename of texture
        if (AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath)) {
            unsigned int textureId = textureNameMap[texturePath.data];
            newMeshInfo.textureIndex = textureId;
        } else {
            newMeshInfo.textureIndex = 0;
        }

        modelMeshes.push_back(newMeshInfo);
    }
}

bool AssimpLoader::Load3DModel(std::string modelFilename) {
    LOGD("~~~Load3DModel()~~~\n");
    LOGI("~~~YJ---fileName = %s~~~\n", modelFilename.c_str());
    LOGI("Scene will be imported now");
    scene = importer->ReadFile(modelFilename.c_str(), aiProcessPreset_TargetRealtime_Quality);

    // Check if import failed
    if (!scene) {
        const char* errorString = importer->GetErrorString();
        LOGE("Scene import failed: %s", errorString);
        return false;
    }
    LOGI("Imported %s successfully.", modelFilename.c_str());

    if(!LoadTextures(modelFilename)) {
        LOGE("Unable to load textures");
        return false;
    }
    LOGI("Loaded textures successfully");

    parseModel();
    LOGI("Loaded vertices and texture coords successfully");

    isObjectLoaded = true;
    return true;
}

bool AssimpLoader::LoadModelMtl(std::string mtlFilename) {
    LOGD("~~~LoadModelMtl()~~~\n");
    return false;
}

bool AssimpLoader::LoadTextures(std::string modelFilename) {
    LOGD("~~~LoadTextures()~~~\n");
    // read names of textures associated with all materials
    textureNameMap.clear();

    for (unsigned int m = 0; m < scene->mNumMaterials; ++m) {

        int textureIndex = 0;
        aiString textureFilename;
        aiReturn isTexturePresent = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE,
                                                                     textureIndex,
                                                                     &textureFilename);
        while (isTexturePresent == AI_SUCCESS) {
            //fill map with textures, OpenGL image ids set to 0
            textureNameMap.insert(std::pair<std::string, GLuint>(textureFilename.data, 0));

            // more textures? more than one texture could be associated with a material
            textureIndex++;
            isTexturePresent = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, textureIndex, &textureFilename);
        }
    }

    int numTextures = (int) textureNameMap.size();
    LOGI("Total number of textures is %d ", numTextures);
    // create and fill array with texture names in GL
    GLuint * textureGLNames = new GLuint[numTextures];
    glGenTextures(numTextures, textureGLNames);

    // Extract the directory part from the file name
    // will be used to read the texture
    std::string modelDirectoryName = FileUtil::getDirectoryName(modelFilename);

    // iterate over the textures, read them using OpenCV, load into GL
    std::map<std::string, GLuint>::iterator textureIterator = textureNameMap.begin();
    int i = 0;
    for (; textureIterator != textureNameMap.end(); ++i, ++textureIterator) {

        std::string textureFilename = (*textureIterator).first;  // get filename
        std::string textureFullPath = modelDirectoryName + "/" + textureFilename;
        (*textureIterator).second = textureGLNames[i];	  // save texture id for filename in map

        // load the texture using OpenCV
        LOGI("Loading texture %s", textureFullPath.c_str());
        cv::Mat textureImage = cv::imread(textureFullPath);
        if (!textureImage.empty()) {

            // opencv reads textures in BGR format, change to RGB for GL
            cv::cvtColor(textureImage, textureImage, CV_BGR2RGBA);
            // opencv reads image from top-left, while GL expects it from bottom-left
            // vertically flip the image
            cv::flip(textureImage, textureImage, 0);

            // bind the texture
            glBindTexture(GL_TEXTURE_2D, textureGLNames[i]);
            // specify linear filtering
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            // load the OpenCV Mat into GLES
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.cols,
                         textureImage.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                         textureImage.data);
        } else {

            LOGE("Couldn't load texture %s", textureFilename.c_str());

            //Cleanup and return
            delete[] textureGLNames;
            return GL_FALSE;

        }
    }
    //Cleanup and return
    delete[] textureGLNames;
    return true;
}

void AssimpLoader::Render3DModel() {
    LOGD("~~~Render3DModel()~~~\n");
    if (!isObjectLoaded) {
        return;
    }

    glUseProgram(program);
    glUniformMatrix4fv(mMVPMatrixHandle, 1, GL_FALSE, MatrixState::getFinalMVPMatrix());

    glActiveTexture(GL_TEXTURE0);
    glUniform1i(mTextureIdHandle, 0);

    unsigned int numberOfLoadedMeshes = modelMeshes.size();

    // render all meshes
    for (unsigned int n = 0; n < numberOfLoadedMeshes; ++n) {

        // Texture
        if (modelMeshes[n].textureIndex) {
            glBindTexture(GL_TEXTURE_2D, modelMeshes[n].textureIndex);
        }

        // Faces
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelMeshes[n].faceBuffer);

        // Vertices
        glBindBuffer(GL_ARRAY_BUFFER, modelMeshes[n].vertexBuffer);
        glEnableVertexAttribArray(mPositionHandle);
        glVertexAttribPointer(mPositionHandle, COORDS_PER_VERTEX, GL_FLOAT, 0, 0, 0);

        // Texture coords
        glBindBuffer(GL_ARRAY_BUFFER, modelMeshes[n].textureCoordBuffer);
        glEnableVertexAttribArray(mTextureCoordHandle);
        glVertexAttribPointer(mTextureCoordHandle, COORDS_PER_TEXTURES, GL_FLOAT, 0, 0, 0);

        glDrawElements(GL_TRIANGLES, modelMeshes[n].numberOfFaces * 3, GL_UNSIGNED_INT, 0);

        // unbind buffers
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void AssimpLoader::Delete3DModel() {
    LOGD("~~~Delete3DModel()~~~\n");
    if (isObjectLoaded) {
        modelMeshes.clear();
        LOGI("Deleted Assimp object");
        isObjectLoaded = false;
    }
}