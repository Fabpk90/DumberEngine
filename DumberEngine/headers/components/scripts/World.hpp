//
// Created by fab on 27/02/2020.
//

#ifndef DUMBERENGINE_WORLD_HPP
#define DUMBERENGINE_WORLD_HPP

#include "Chunk.hpp"
#include "../IComponent.hpp"
#include "../../rendering/helper/Shader.hpp"

class World : public IComponent
{
public:
    static const int CHUNK_SIZE = 1;

private:
    Chunk *chunks[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    Shader shaderWorld;
public:
    ~World();
    World();

    void start() override;

    void update() override;

    void draw() override;

    void drawInspector() override;
};

#endif //DUMBERENGINE_WORLD_HPP
