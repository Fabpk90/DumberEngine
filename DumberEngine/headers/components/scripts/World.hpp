//
// Created by fab on 27/02/2020.
//

#ifndef DUMBERENGINE_WORLD_HPP
#define DUMBERENGINE_WORLD_HPP

#include "Chunk.hpp"
#include "../IComponent.hpp"
#include "../../rendering/helper/Shader.hpp"
#include "../../rendering/renderer/opengl/Texture2D.hpp"

class World : public IComponent
{
public:
    static const int CHUNK_SIZE = 1;

private:
    Chunk *chunks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Shader shaderWorld;
    Texture2D texture;
    glm::vec3 sunDirection;
    glm::vec3 skyColor;
    glm::vec3 sunColor;

    void setNeighborhood();

public:
    ~World();
    World();

    void start() override;

    void update() override;

    void draw() override;

    void drawInspector() override;

    void deleteCube(int x, int y, int z);

    Cube *getCube(int x, int y, int z);

    void updateCube(int x, int y, int z);

    Chunk *getChunkAt(int x, int y, int z);
};

#endif //DUMBERENGINE_WORLD_HPP
