//
// Created by fab on 31/05/2020.
//

#include "../../../headers/components/rendering/Mesh.hpp"

#include <utility>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures)
: vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures))
{

}

void Mesh::Draw(Shader shader)
{

}

void Mesh::setupMesh()
{

}

