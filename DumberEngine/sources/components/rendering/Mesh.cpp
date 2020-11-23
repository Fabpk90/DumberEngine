//
// Created by fab on 31/05/2020.
//

#include "../../../headers/components/rendering/Mesh.hpp"

#include <utility>


void Mesh::draw(Shader* shader)
{
    glBindVertexArray(vao);
    int i = 0;
    for(auto& tex : textures)
    {
        switch (tex->getType())
        {
            case ITexture::Albedo:
                tex->use(i);
                shader->setInt("t_albedo", i);
                i++;
                break;

            case ITexture::Metalness:
                tex->use(i);
                shader->setInt("t_metallic", i);
                i++;
                break;

            case ITexture::AO:
                tex->use(i);
                shader->setInt("t_ao", i);
                i++;
                break;

            case ITexture::Roughness:
                tex->use(i);
                shader->setInt("t_roughness", i);
                i++;
                break;
        }
    }

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<unsigned int> &indices, std::vector<Texture2D*> &textures)
: vertices(std::move(vertices)), indices(std::move(indices)), textures(std::move(textures))
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->vertices.size(), this->vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->indices.size(), this->indices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 3));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void*)(sizeof(float) * 6));
}

Texture2D *Mesh::getTextureByType(Texture2D::ETextureType type)
{
    for(const auto tex : textures)
    {
        if(tex->getType() == type)
            return tex;
    }

    return nullptr;
}

