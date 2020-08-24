//
// Created by fab on 31/05/2020.
//

#include "../../../headers/components/rendering/Mesh.hpp"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures)
{

}

void Mesh::Draw(Shader shader)
{

}

void Mesh::setupMesh()
{
    /*Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("path", aiProcess_Triangulate | aiProcess_FlipUVs);*/
}

