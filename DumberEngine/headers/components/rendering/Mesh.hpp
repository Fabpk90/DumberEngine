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
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture2D> textures);
    void Draw(Shader shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};
#endif //DUMBERENGINE_MESH_HPP
