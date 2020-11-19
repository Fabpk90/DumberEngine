//
// Created by fab on 20/11/2020.
//

#include <fstream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include "../../../headers/components/IComponent.hpp"
#include "../../../headers/components/rendering/StaticMesh.hpp"

void StaticMesh::draw()
{
    IComponent::draw();
}


void StaticMesh::loadFrom(const char *path)
{
    //TODO: add an assetloader to map stuff already loaded

    std::ifstream file(path);

    if(!file.bad())
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

        meshes.resize(scene->mNumMeshes);

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
}

Mesh* StaticMesh::loadMeshFrom(aiMesh &mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D> textures;

    vertices.reserve(mesh.mNumVertices);
    indices.reserve(mesh.mNumFaces);


    return new Mesh(vertices, indices, textures);
}
