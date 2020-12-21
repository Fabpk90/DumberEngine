//
// Created by fab on 27/02/2020.
//

#include <imgui/imgui.h>
#include <iostream>
#include "../../../headers/components/scripts/World.hpp"
#include "../../../headers/rendering/renderer/Camera.hpp"
#include "../../../headers/rendering/helper/Time.hpp"
#include "../../../headers/rendering/Scene.hpp"
#include "../../../headers/systems/rendering/ShadowMapping.hpp"

glm::vec3 World::sunDirection = glm::vec3(0);

void World::start()
{

}

void World::update()
{

}

void World::draw()
{

    debug->draw();

    shaderWorld.use();

    glm::mat4 m = Scene::instance->getGameObject(*gameObjectIndex)->getTransform().getModelMatrix();
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

    shaderWorld.setMatrix4("lightSpaceMatrix", ShadowMapping::getInstance()->getProjectionMatrix());

    texture.use(0);
    shaderWorld.setInt("worldTex", 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, ShadowMapping::getInstance()->getFbo().getDepthTexture());
    shaderWorld.setInt("shadowTex",  1);

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
    IWindow::instance->setClearColor(skyColor);
    ImGui::DragFloat3("SunColor", &sunColor.x, 0.01f);
    if(ImGui::DragFloat3("SunDirection", &sunDirection.x, 0.01f))
    {
        debug->setPosition(sunDirection);
    }
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

    texture.loadFrom("textures/terrain.png", ITexture::Diffuse);

    sunColor = glm::vec3(1.0f, 1.0f, 0.8f);
    skyColor = glm::vec3(0.0f, 181.f / 255.f, 221.f / 255.f);
    sunDirection = glm::vec3(20, 65, 12);

    debug = new CubeDebug(sunDirection);

    IWindow::instance->setClearColor(skyColor);
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
    if(x >= 0 && x < CHUNK_SIZE
    && y >= 0 && y < CHUNK_SIZE
    && z >= 0 && z < CHUNK_SIZE)
        return chunks[x][y][z];

    return nullptr;
}

void World::drawShadow(Shader *pShader)
{
    glm::mat4 m = Scene::instance->getGameObject(*gameObjectIndex)->getTransform().getModelMatrix();
    pShader->setMatrix4("model", m);
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            for (int k = 0; k < CHUNK_SIZE; ++k)
            {
                chunks[i][j][k]->draw(false);
            }
        }
    }
}

World::MAxis World::getMinCol(glm::vec3 pos, glm::vec3 dir, float width, float height, float &valueColMin, bool oneShot)
{
    int x = (int)(pos.x / Cube::CUBE_SIZE);
    int y = (int)(pos.y / Cube::CUBE_SIZE);
    int z = (int)(pos.z / Cube::CUBE_SIZE);

    if (getCube(x, y, z) == nullptr) return 0;


    int xNext = (int)((pos.x + width / 2.0f) / Cube::CUBE_SIZE);
    int yNext = (int)((pos.y + width / 2.0f) / Cube::CUBE_SIZE);
    int zNext = (int)((pos.z + height / 2.0f) / Cube::CUBE_SIZE);

    int xPrev = (int)((pos.x - width / 2.0f) / Cube::CUBE_SIZE);
    int yPrev = (int)((pos.y - width / 2.0f) / Cube::CUBE_SIZE);
    int zPrev = (int)((pos.z - height / 2.0f) / Cube::CUBE_SIZE);

    if (x < 0)	x = 0;
    if (y < 0)	y = 0;
    if (z < 0)	z = 0;

    if (xPrev < 0)	xPrev = 0;
    if (yPrev < 0)	yPrev = 0;
    if (zPrev < 0)	zPrev = 0;

    if (xNext < 0)	xNext = 0;
    if (yNext < 0)	yNext = 0;
    if (zNext < 0)	zNext = 0;

    if (x >= Chunk::CUBE_IN_CHUNK)	x = Chunk::CUBE_IN_CHUNK - 1;
    if (y >= Chunk::CUBE_IN_CHUNK)	y = Chunk::CUBE_IN_CHUNK - 1;
    if (z >= Chunk::CUBE_IN_CHUNK)	z = Chunk::CUBE_IN_CHUNK - 1;

    if (xPrev >= Chunk::CUBE_IN_CHUNK)	xPrev = Chunk::CUBE_IN_CHUNK - 1;
    if (yPrev >= Chunk::CUBE_IN_CHUNK)	yPrev = Chunk::CUBE_IN_CHUNK - 1;
    if (zPrev >= Chunk::CUBE_IN_CHUNK)	zPrev = Chunk::CUBE_IN_CHUNK - 1;

    if (xNext >= Chunk::CUBE_IN_CHUNK)	xNext = Chunk::CUBE_IN_CHUNK - 1;
    if (yNext >= Chunk::CUBE_IN_CHUNK)	yNext = Chunk::CUBE_IN_CHUNK - 1;
    if (zNext >= Chunk::CUBE_IN_CHUNK)	zNext = Chunk::CUBE_IN_CHUNK - 1;

    //On fait chaque axe
    MAxis axis = 0x00;
    valueColMin = oneShot ? 0.5f : 10000.0f;
    float seuil = 0.0000001f;
    float prodScalMin = 1.0f;
    if (dir.length() > 1)
        dir = glm::normalize(dir);

    //On verif tout les 4 angles de gauche
    if (getCube(xPrev, yPrev, zPrev)->isSolid() ||
        getCube(xPrev, yPrev, zNext)->isSolid() ||
        getCube(xPrev, yNext, zPrev)->isSolid() ||
        getCube(xPrev, yNext, zNext)->isSolid())
    {
        //On verif que resoudre cette collision est utile
        if (!(getCube(xPrev + 1, yPrev, zPrev)->isSolid() ||
              getCube(xPrev + 1, yPrev, zNext)->isSolid() ||
              getCube(xPrev + 1, yNext, zPrev)->isSolid() ||
              getCube(xPrev + 1, yNext, zNext)->isSolid()) || !oneShot)
        {
            float depassement = ((xPrev + 1) * Cube::CUBE_SIZE) - (pos.x - width / 2.0f);
            float prodScal = abs(dir.x);
            if (abs(depassement) > seuil)
                if (abs(depassement) < abs(valueColMin))
                {
                    prodScalMin = prodScal;
                    valueColMin = depassement;
                    axis = AXIS_X;
                }
        }
    }

    //float depassementx2 = (xNext * NYCube::CUBE_SIZE) - (pos.X + width / 2.0f);

    //On verif tout les 4 angles de droite
    if (getCube(xNext, yPrev, zPrev)->isSolid() ||
        getCube(xNext, yPrev, zNext)->isSolid() ||
        getCube(xNext, yNext, zPrev)->isSolid() ||
        getCube(xNext, yNext, zNext)->isSolid())
    {
        //On verif que resoudre cette collision est utile
        if (!(getCube(xNext - 1, yPrev, zPrev)->isSolid() ||
              getCube(xNext - 1, yPrev, zNext)->isSolid() ||
              getCube(xNext - 1, yNext, zPrev)->isSolid() ||
              getCube(xNext - 1, yNext, zNext)->isSolid()) || !oneShot)
        {
            float depassement = (xNext * Cube::CUBE_SIZE) - (pos.x + width / 2.0f);
            float prodScal = abs(dir.x);
            if (abs(depassement) > seuil)
                if (abs(depassement) < abs(valueColMin))
                {
                    prodScalMin = prodScal;
                    valueColMin = depassement;
                    axis = AXIS_X;
                }
        }
    }

    //float depassementy1 = (yNext * NYCube::CUBE_SIZE) - (pos.Y + width / 2.0f);

    //On verif tout les 4 angles de devant
    if (getCube(xPrev, yNext, zPrev)->isSolid() ||
        getCube(xPrev, yNext, zNext)->isSolid() ||
        getCube(xNext, yNext, zPrev)->isSolid() ||
        getCube(xNext, yNext, zNext)->isSolid())
    {
        //On verif que resoudre cette collision est utile
        if (!(getCube(xPrev, yNext - 1, zPrev)->isSolid() ||
              getCube(xPrev, yNext - 1, zNext)->isSolid() ||
              getCube(xNext, yNext - 1, zPrev)->isSolid() ||
              getCube(xNext, yNext - 1, zNext)->isSolid()) || !oneShot)
        {
            float depassement = (yNext * Cube::CUBE_SIZE) - (pos.y + width / 2.0f);
            float prodScal = abs(dir.y);
            if (abs(depassement) > seuil)
                if (abs(depassement) < abs(valueColMin))
                {
                    prodScalMin = prodScal;
                    valueColMin = depassement;
                    axis = AXIS_Y;
                }
        }
    }

    //float depassementy2 = ((yPrev + 1) * NYCube::CUBE_SIZE) - (pos.Y - width / 2.0f);

    //On verif tout les 4 angles de derriere
    if (getCube(xPrev, yPrev, zPrev)->isSolid() ||
        getCube(xPrev, yPrev, zNext)->isSolid() ||
        getCube(xNext, yPrev, zPrev)->isSolid() ||
        getCube(xNext, yPrev, zNext)->isSolid())
    {
        //On verif que resoudre cette collision est utile
        if (!(getCube(xPrev, yPrev + 1, zPrev)->isSolid() ||
              getCube(xPrev, yPrev + 1, zNext)->isSolid() ||
              getCube(xNext, yPrev + 1, zPrev)->isSolid() ||
              getCube(xNext, yPrev + 1, zNext)->isSolid()) || !oneShot)
        {
            float depassement = ((yPrev + 1) * Cube::CUBE_SIZE) - (pos.y - width / 2.0f);
            float prodScal = abs(dir.y);
            if (abs(depassement) > seuil)
                if (abs(depassement) < abs(valueColMin))
                {
                    prodScalMin = prodScal;
                    valueColMin = depassement;
                    axis = AXIS_Y;
                }
        }
    }

    //On verif tout les 4 angles du haut
    if (getCube(xPrev, yPrev, zNext)->isSolid() ||
        getCube(xPrev, yNext, zNext)->isSolid() ||
        getCube(xNext, yPrev, zNext)->isSolid() ||
        getCube(xNext, yNext, zNext)->isSolid())
    {
        //On verif que resoudre cette collision est utile
        if (!(getCube(xPrev, yPrev, zNext - 1)->isSolid() ||
              getCube(xPrev, yNext, zNext - 1)->isSolid() ||
              getCube(xNext, yPrev, zNext - 1)->isSolid() ||
              getCube(xNext, yNext, zNext - 1)->isSolid()) || !oneShot)
        {
            float depassement = (zNext * Cube::CUBE_SIZE) - (pos.z + height / 2.0f);
            float prodScal = abs(dir.z);
            if (abs(depassement) > seuil)
                if (abs(depassement) < abs(valueColMin))
                {
                    prodScalMin = prodScal;
                    valueColMin = depassement;
                    axis = AXIS_Z;
                }
        }
    }

    //On verif tout les 4 angles du bas
    if (getCube(xPrev, yPrev, zPrev)->isSolid() ||
        getCube(xPrev, yNext, zPrev)->isSolid() ||
        getCube(xNext, yPrev, zPrev)->isSolid() ||
        getCube(xNext, yNext, zPrev)->isSolid())
    {
        //On verif que resoudre cette collision est utile
        if (!(getCube(xPrev, yPrev, zPrev + 1)->isSolid() ||
              getCube(xPrev, yNext, zPrev + 1)->isSolid() ||
              getCube(xNext, yPrev, zPrev + 1)->isSolid() ||
              getCube(xNext, yNext, zPrev + 1)->isSolid()) || !oneShot)
        {
            float depassement = ((zPrev + 1) * Cube::CUBE_SIZE) - (pos.z - height / 2.0f);
            float prodScal = abs(dir.z);
            if (abs(depassement) > seuil)
                if (abs(depassement) < abs(valueColMin))
                {
                    prodScalMin = prodScal;
                    valueColMin = depassement;
                    axis = AXIS_Z;
                }
        }
    }

    return axis;
}
