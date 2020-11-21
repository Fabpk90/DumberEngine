//
// Created by fab on 20/11/2020.
//

#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <iostream>
#include "../../../headers/components/IComponent.hpp"
#include "../../../headers/components/rendering/StaticMesh.hpp"
#include "../../../headers/rendering/renderer/Camera.hpp"

void StaticMesh::draw()
{
    shader->use();

    shader->setMatrix4("m", transform->getModelMatrix());
    glm::mat4 v = Camera::getInstance().getViewMatrix();
    shader->setMatrix4("v", v);
    auto p = Camera::getInstance().getProjectionMatrix();
    shader->setMatrix4("p", p);

    for(const auto mesh : meshes)
    {
        mesh->Draw(*shader);
    }
}


void StaticMesh::loadFrom(const char *path)
{
    this->path = path;
    auto index = this->path.find_last_of('/') + 1; // +1 to include the /
    this->path = this->path.substr(0, index);
    //TODO: add an assetloader to map stuff already loaded

    std::ifstream file(path);

    if(!file.bad())
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        meshes.reserve(scene->mNumMeshes);

        recursivelyLoadNode(scene->mRootNode, scene);

        importer.FreeScene();
    }
}

void StaticMesh::recursivelyLoadNode(aiNode *const pNode, const aiScene *pScene)
{
    for(int i = 0; i < pNode->mNumMeshes; i++)
    {
        meshes.emplace_back(loadMeshFrom(*pScene->mMeshes[pNode->mMeshes[i]], pScene));
    }

    for(int i = 0; i < pNode->mNumChildren; i++)
    {
        recursivelyLoadNode(pNode->mChildren[i], pScene);
    }
}

Mesh* StaticMesh::loadMeshFrom(aiMesh &mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D> textures;

    vertices.reserve(mesh.mNumVertices);
    indices.reserve(mesh.mNumFaces);


    for(int i = 0; i < mesh.mNumVertices; i++)
    {
        Vertex v{};

        v.Position.x = mesh.mVertices[i].x;
        v.Position.y = mesh.mVertices[i].y;
        v.Position.z = mesh.mVertices[i].z;

        v.Normal.x = mesh.mNormals[i].x;
        v.Normal.y = mesh.mNormals[i].y;
        v.Normal.z = mesh.mNormals[i].z;

        v.TexCoords.x = mesh.mTextureCoords[0][i].x;
        v.TexCoords.y = mesh.mTextureCoords[0][i].y;

        vertices.emplace_back(v);
    }

    for(int i = 0; i < mesh.mNumFaces; i++)
    {
        auto face = mesh.mFaces[i];

        for(int j = 0; j < face.mNumIndices; j++)
        {
            indices.emplace_back(face.mIndices[j]);
        }
    }

    //the mesh has some materials
    if(mesh.mMaterialIndex >= 0)
    {
        auto mat = scene->mMaterials[mesh.mMaterialIndex];

        auto texDiffuse = loadMaterialTexturesType(mat, aiTextureType_DIFFUSE);
        textures = texDiffuse;

        auto texSpecular = loadMaterialTexturesType(mat, aiTextureType_SPECULAR);

        if(texSpecular.empty())
        {
            texSpecular = loadMaterialTexturesType(mat, aiTextureType_HEIGHT);
        }

        textures.insert(textures.end(), texSpecular.begin(), texSpecular.end());
    }

    return new Mesh(vertices, indices, textures);
}

std::vector<Texture2D> StaticMesh::loadMaterialTexturesType(aiMaterial *pMaterial, aiTextureType type)
{
    std::vector<Texture2D> tex;

    tex.resize(pMaterial->GetTextureCount(type));

    for(int i = 0; i < pMaterial->GetTextureCount(type); i++)
    {
        aiString texturePath;

        if(pMaterial->GetTexture(type, i, &texturePath) == aiReturn_SUCCESS)
        {
            std::string texPath(path);
            texPath.append(texturePath.C_Str());

            tex[i].loadFrom(texPath.c_str(), ITexture::convertFrom(type));
        }
    }

    return tex;
}

void StaticMesh::start()
{
    shader = new Shader("shaders/mesh/");

    transform->setPosition(0, 0, 0);
}

StaticMesh::~StaticMesh()
{
    delete shader;

    for(auto mesh : meshes)
        delete mesh;
}
