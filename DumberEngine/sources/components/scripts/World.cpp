//
// Created by fab on 27/02/2020.
//

#include "../../../headers/components/scripts/World.hpp"
#include "../../../headers/rendering/renderer/Camera.hpp"

void World::start()
{

}

void World::update()
{

}

void World::draw()
{
    shaderWorld.use();
    glm::mat4 m = glm::mat4(1.0f);
    shaderWorld.setMatrix4("m", m);
    glm::mat4 v = Camera::getInstance().getViewMatrix();
    shaderWorld.setMatrix4("v", v);
    auto p = Camera::getInstance().getProjectionMatrix();
    shaderWorld.setMatrix4("p", p);

    texture.use(0);
    shaderWorld.setInt("worldTex", 0);

    bool isTransparentPass = false;
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE; ++k)
            {
                chunks[i][k][j]->draw(isTransparentPass);
            }
        }
    }

    isTransparentPass = true;

    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE; ++k)
            {
                chunks[i][k][j]->draw(isTransparentPass);
            }
        }
    }
}

void World::drawInspector()
{

}

World::World() : shaderWorld("shaders/cube/")
{
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE; ++k)
            {
                chunks[i][k][j] = new Chunk(i, j, k);
            }
        }
    }

    texture.loadFrom("textures/terrain.png");
}

World::~World()
{
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE; ++k)
            {
                delete chunks[i][j][k];
            }
        }
    }
}
