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

    void foreachVisibleTriangle(bool countOnly, int * nbVertOpaque, int * nbVertTrasp, Vbo * VboOpaque, Vbo * VboTrasparent);
    void get_surrounding_cubes(int x, int y, int z, Cube ** cubeXPrev, Cube ** cubeXNext,
                               Cube ** cubeYPrev, Cube ** cubeYNext,
                               Cube ** cubeZPrev, Cube ** cubeZNext);

public:
    static const int CUBE_IN_CHUNK = 64;

    Cube cubes[CUBE_IN_CHUNK][CUBE_IN_CHUNK][CUBE_IN_CHUNK];
    Vbo* vboOpaque;
    Vbo* vboTransparent;

    Chunk* neighborhood[6];

    glm::vec3 chunkPosition;

    ~Chunk();
    Chunk(glm::vec3 position);
    Chunk(int x, int y, int z);

    void toVbo();

    void draw(bool isTransparentPass);

    void setNeighboors(Chunk *xPrev, Chunk *xNext, Chunk *yPrev, Chunk *yNext, Chunk *zPrev, Chunk *zNext);

    bool testHiddenCube(int x, int y, int z);
    void disableHiddenCubes();

    Cube *getCubeAt(int x, int y, int z);
};

#endif //DUMBERENGINE_CHUNK_HPP
