//
// Created by fab on 27/02/2020.
//

#ifndef DUMBERENGINE_CHUNK_HPP
#define DUMBERENGINE_CHUNK_HPP

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../IComponent.hpp"
#include "Cube.hpp"
#include "../../rendering/renderer/opengl/Vbo.hpp"

#define CUBE_MASK_TRANSPARENT 0xFF

class Chunk
{
private:
    glm::vec2 getAtlasPosition(float type);
    void countCube(unsigned int& transparent, unsigned int& opaque);
    void addQuadToVbo(Vbo* vbo, int& vertexIndex, glm::vec3& a, glm::vec3& b, glm::vec3& c, glm::vec3& d, float type);
    void addCubeToVbo(Vbo* vbo, int& vertexIndex, glm::ivec3 position, float type);

    void initCubes();


public:
    static const int CUBE_IN_CHUNK = 64;

    Cube cubes[CUBE_IN_CHUNK][CUBE_IN_CHUNK][CUBE_IN_CHUNK];
    Vbo* vboOpaque;
    Vbo* vboTransparent;

    glm::vec3 chunkPosition;

    ~Chunk();
    Chunk(glm::vec3 position);
    Chunk(int x, int y, int z);

    void toVbo();

    void draw(bool isTransparentPass);
};

#endif //DUMBERENGINE_CHUNK_HPP
