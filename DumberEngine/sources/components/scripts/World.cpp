//
// Created by fab on 27/02/2020.
//

#include <imgui/imgui.h>
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



    shaderWorld.setVec3("lightDir", sunDirection);

    shaderWorld.setVec3("skyColor", skyColor);

    shaderWorld.setVec3("sunColor", sunColor);

    shaderWorld.setVec3("camPosition", Camera::getInstance().position);

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
    ImGui::Text("World: %d chunks ", CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE);
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

    texture.loadFrom("textures/terrain.png");

    sunColor = glm::vec3(1.0f, 1.0f, 0.8f);
    skyColor = glm::vec3(0.0f, 181.f / 255.f, 221.f / 255.f);
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
