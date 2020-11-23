//
// Created by fab on 31/05/2020.
//

#ifndef DUMBERENGINE_MESH_HPP
#define DUMBERENGINE_MESH_HPP

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include "../../utils/MeshLoader.hpp"
#include "../../rendering/helper/Shader.hpp"
#include "../../rendering/renderer/opengl/Texture2D.hpp"

class Mesh {
public:
    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture2D*>& textures);
    void draw(Shader* shader);

    ~Mesh()
    {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);

        for(auto tex : textures)
            delete tex;
    };

    std::vector<Texture2D*>& getTextures() { return textures; }
    Texture2D* getTextureByType(Texture2D::ETextureType type);
private:
    //  render data
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D*>      textures;
};
#endif //DUMBERENGINE_MESH_HPP
