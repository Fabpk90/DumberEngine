//
// Created by fab on 27/02/2020.
//

#include <imgui/imgui.h>
#include <iostream>
#include "../../../headers/components/scripts/World.hpp"
#include "../../../headers/rendering/renderer/Camera.hpp"
#include "../../../headers/rendering/helper/Time.hpp"
#include "../../../headers/rendering/Scene.hpp"

void World::start()
{

}

void World::update()
{

}

void World::draw()
{
    shaderWorld.use();

    glm::mat4 m = Scene::getGameObject(gameObjectIndex)->getTransform().getModelMatrix();
    shaderWorld.setMatrix4("m", m);
    glm::mat4 v = Camera::getInstance().getViewMatrix();
    shaderWorld.setMatrix4("v", v);
    auto p = Camera::getInstance().getProjectionMatrix();
    shaderWorld.setMatrix4("p", p);



    shaderWorld.setVec3("lightDir", sunDirection);

    shaderWorld.setVec3("skyColor", skyColor);
    shaderWorld.setVec3("sunColor", sunColor);

    shaderWorld.setVec3("camPosition", Camera::getInstance().position);

    shaderWorld.setFloat("elapsed", Time::getInstance().time);

    texture.use(0);
    shaderWorld.setInt("worldTex", 0);

    bool isTransparentPass = false;
    glDisable(GL_BLEND);
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
    glEnable(GL_BLEND);
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
    ImGui::Text("%d chunks ", CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
    ImGui::DragFloat3("SkyColor", &skyColor.x, 0.01f);
    ImGui::DragFloat3("SunColor", &sunColor.x, 0.01f);
    ImGui::DragFloat3("SunDirection", &sunDirection.x, 0.01f);
}

World::World() : shaderWorld("shaders/world/")
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

    setNeighborhood();
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE; ++k)
            {
                chunks[i][k][j]->disableHiddenCubes();
                chunks[i][k][j]->toVbo();
            }
        }
    }

    texture.loadFrom("textures/terrain.png");

    sunColor = glm::vec3(1.0f, 1.0f, 0.8f);
    skyColor = glm::vec3(0.0f, 181.f / 255.f, 221.f / 255.f);
    sunDirection = glm::vec3(0, 1, 0);
}

void World::setNeighborhood()
{
    for(int x=0;x<CHUNK_SIZE;x++)
        for(int y=0;y<CHUNK_SIZE;y++)
            for(int z=0;z<CHUNK_SIZE;z++)
            {
                Chunk * cxPrev = NULL;
                if(x > 0)
                    cxPrev = chunks[x-1][y][z];
                Chunk * cxNext = NULL;
                if(x < CHUNK_SIZE-1)
                    cxNext = chunks[x+1][y][z];

                Chunk * cyPrev = NULL;
                if(y > 0)
                    cyPrev = chunks[x][y-1][z];
                Chunk * cyNext = NULL;
                if(y < CHUNK_SIZE-1)
                    cyNext = chunks[x][y+1][z];

                Chunk * czPrev = NULL;
                if(z > 0)
                    czPrev = chunks[x][y][z-1];
                Chunk * czNext = NULL;
                if(z < CHUNK_SIZE-1)
                    czNext = chunks[x][y][z+1];

                chunks[x][y][z]->setNeighboors(cxPrev,cxNext,cyPrev,cyNext,czPrev,czNext);
            }
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

void World::deleteCube(int x, int y, int z)
{
    std::cout << "bong" << std::endl;
    Cube * cube = getCube(x,y,z);
    cube->setType(Cube::CUBE_AIR);
    cube->setDraw(false);
    updateCube(x,y,z);
}

Cube *World::getCube(int x, int y, int z)
{
    if (x < 0)x = 0;
    if (y < 0)y = 0;
    if (z < 0)z = 0;

    int xIndex = x / Chunk::CUBE_IN_CHUNK;
    int yIndex = y / Chunk::CUBE_IN_CHUNK;
    int zIndex = z / Chunk::CUBE_IN_CHUNK;

    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE; ++k)
            {
                auto chunk = chunks[i][j][k];
                if(chunk->chunkPosition.x == xIndex
                  && chunk->chunkPosition.y == yIndex
                  && chunk->chunkPosition.z == zIndex)
                {
                    return chunk->getCubeAt(x % Chunk::CUBE_IN_CHUNK, y % Chunk::CUBE_IN_CHUNK, z % Chunk::CUBE_IN_CHUNK);
                }
            }
        }
    }

    return nullptr;
}

void World::updateCube(int x, int y, int z)
{
    int xIndex = x / Chunk::CUBE_IN_CHUNK;
    int yIndex = y / Chunk::CUBE_IN_CHUNK;
    int zIndex = z / Chunk::CUBE_IN_CHUNK;

    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE; ++k)
            {
                auto chunk = chunks[i][j][k];
                if(chunk->chunkPosition.x == xIndex
                   && chunk->chunkPosition.y == yIndex
                   && chunk->chunkPosition.z == zIndex)
                {
                    chunk->disableHiddenCubes();
                    chunk->toVbo();
                }
            }
        }
    }
}

Chunk *World::getChunkAt(int x, int y, int z)
{
    return chunks[x][y][z];
}
