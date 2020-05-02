//
// Created by fab on 27/02/2020.
//

#ifndef DUMBERENGINE_WORLD_HPP
#define DUMBERENGINE_WORLD_HPP

#include "Chunk.hpp"
#include "../IComponent.hpp"
#include "../../rendering/helper/Shader.hpp"
#include "../../rendering/renderer/opengl/Texture2D.hpp"
#include "../../debug/CubeDebug.hpp"

class World : public IComponent
{
public:
    static const int CHUNK_SIZE = 1;

    typedef uint8_t MAxis;
    static const int AXIS_X = 0b00000001;
    static const int AXIS_Y = 0b00000010;
    static const int AXIS_Z = 0b00000100;

private:
    Chunk *chunks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Shader shaderWorld;
    Texture2D texture;

    glm::vec3 skyColor;
    glm::vec3 sunColor;

    CubeDebug* debug;

    void setNeighborhood();

public:

    static glm::vec3 sunDirection;

    ~World();
    World();

    void start() override;

    void update() override;

    void draw() override;

    void drawShadow(Shader *pShader) override;
    bool castShadow() { return true; }

    void drawInspector() override;

    void deleteCube(int x, int y, int z);

    Cube *getCube(int x, int y, int z);

    void updateCube(int x, int y, int z);

    Chunk *getChunkAt(int x, int y, int z);

    MAxis getMinCol(glm::vec3 pos, glm::vec3 dir, float width, float height, float & valueColMin, bool oneShot);
};

#endif //DUMBERENGINE_WORLD_HPP
