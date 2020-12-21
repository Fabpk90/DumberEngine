//
// Created by fab on 31/05/2020.
//

#ifndef DUMBERENGINE_VERTEX_HPP
#define DUMBERENGINE_VERTEX_HPP

#include <glm/glm.hpp>
#include <cereal/archives/portable_binary.hpp>

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;

    template<class Archive>
    void serialize(Archive& archive)
    {
        archive(Position.x, Position.y, Position.z, Normal.x, Normal.y, Normal.z, TexCoords.x, TexCoords.y);
    }
};
#endif //DUMBERENGINE_VERTEX_HPP
