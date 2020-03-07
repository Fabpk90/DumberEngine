//
// Created by fab on 27/02/2020.
//

#include "../../../headers/components/scripts/Chunk.hpp"
#include "../../../headers/utils/PerlinNoise.hpp"
#include <glm/glm.hpp>
#include <iostream>

Chunk::Chunk(glm::vec3 position) : chunkPosition(position)
{
    vboOpaque = vboTransparent = nullptr;
    initCubes();
}

Chunk::Chunk(int x, int y, int z) : chunkPosition(x, y, z)
{
    vboOpaque = vboTransparent = nullptr;
    initCubes();
}

void Chunk::draw(bool isTransparentPass)
{
    if(isTransparentPass && vboTransparent != nullptr)
    {
        vboTransparent->draw();
    }
    else if(vboOpaque != nullptr)
    {
        vboOpaque->draw();
    }
}

void Chunk::toVbo()
{
    unsigned int transparentCubes = 0, opaqueCubes = 0;

    countCube(transparentCubes, opaqueCubes);

    delete vboTransparent;
    delete vboOpaque;

    vboOpaque = new Vbo(4, opaqueCubes * 36);

    vboOpaque->setElementDescription(0, Vbo::Element(3));
    vboOpaque->setElementDescription(1, Vbo::Element(3));
    vboOpaque->setElementDescription(2, Vbo::Element(2));
    vboOpaque->setElementDescription(3, Vbo::Element(1));

    vboOpaque->createCPUSide();

    vboTransparent = new Vbo(4, transparentCubes * 36);

    vboTransparent->setElementDescription(0, Vbo::Element(3));
    vboTransparent->setElementDescription(1, Vbo::Element(3));
    vboTransparent->setElementDescription(2, Vbo::Element(2));
    vboTransparent->setElementDescription(3, Vbo::Element(1));

    vboTransparent->createCPUSide();

    int vertexIndexTransparent = 0, vertexIndexOpaque = 0;
    for (int i = 0; i < CUBE_IN_CHUNK; ++i)
    {
        for (int j = 0; j < CUBE_IN_CHUNK; ++j)
        {
            for (int k = 0; k < CUBE_IN_CHUNK; ++k)
            {
                auto& cube = cubes[i][j][k];

                if(cube.getType() != Cube::CUBE_AIR)
                {
                    if(cube.isTransparent())
                        addCubeToVbo(vboTransparent, vertexIndexTransparent, glm::vec3(i, j, k), cube.getType());
                    else
                        addCubeToVbo(vboOpaque, vertexIndexOpaque, glm::vec3(i, j, k),  cube.getType());
                }
            }
        }
    }

    vboOpaque->createGPUSide();
    vboTransparent->createGPUSide();
}

void Chunk::addQuadToVbo(Vbo *vbo, int& vertexIndex, glm::vec3 &a, glm::vec3 &b, glm::vec3 &c, glm::vec3 &d, float type)
{
    glm::vec3 normal = glm::cross(glm::normalize(b - a), glm::normalize(c - a));
    glm::vec2 uvPosition = 0.0625f * getAtlasPosition(type);

    vbo->setElementData(0, vertexIndex, a.x, a.y, a.z);
    vbo->setElementData(1, vertexIndex, normal.x, normal.y, normal.z);
    vbo->setElementData(2, vertexIndex, uvPosition.x , uvPosition.y + 0.0625f);
    vbo->setElementData(3, vertexIndex, type);
    ++vertexIndex;
    vbo->setElementData(0, vertexIndex, b.x, b.y, b.z);
    vbo->setElementData(1, vertexIndex, normal.x, normal.y, normal.z);
    vbo->setElementData(2, vertexIndex, uvPosition.x + 0.0625f, uvPosition.y + 0.0625f);
    vbo->setElementData(3, vertexIndex, type);
    ++vertexIndex;
    vbo->setElementData(0, vertexIndex, c.x, c.y, c.z);
    vbo->setElementData(1, vertexIndex, normal.x, normal.y, normal.z);
    vbo->setElementData(2, vertexIndex, uvPosition.x + 0.0625f, uvPosition.y);
    vbo->setElementData(3, vertexIndex, type);
    ++vertexIndex;

    vbo->setElementData(0, vertexIndex, a.x, a.y, a.z);
    vbo->setElementData(1, vertexIndex, normal.x, normal.y, normal.z);
    vbo->setElementData(2, vertexIndex, uvPosition.x, uvPosition.y + 0.0625f);
    vbo->setElementData(3, vertexIndex, type);
    ++vertexIndex;
    vbo->setElementData(0, vertexIndex, c.x, c.y, c.z);
    vbo->setElementData(1, vertexIndex, normal.x, normal.y, normal.z);
    vbo->setElementData(2, vertexIndex, uvPosition.x + 0.0625f, uvPosition.y);
    vbo->setElementData(3, vertexIndex, type);
    ++vertexIndex;
    vbo->setElementData(0, vertexIndex, d.x, d.y, d.z);
    vbo->setElementData(1, vertexIndex, normal.x, normal.y, normal.z);
    vbo->setElementData(2, vertexIndex, uvPosition.x, uvPosition.y);
    vbo->setElementData(3, vertexIndex, type);
    ++vertexIndex;
}

void Chunk::addCubeToVbo(Vbo *vbo, int& vertexIndex, glm::ivec3 position, float type)
{
    const int size = Cube::CUBE_SIZE;
    glm::vec3 a, b, c, d;
    const int trueX = (position.x * size) + chunkPosition.x * CUBE_IN_CHUNK;
    const int trueY = (position.y * size) + chunkPosition.y * CUBE_IN_CHUNK;
    const int trueZ = (position.z * size) + chunkPosition.z * CUBE_IN_CHUNK;


    b = glm::vec3(trueX, trueY + size, trueZ);
    c = glm::vec3(trueX, trueY + size, trueZ + size);
    d = glm::vec3(trueX + size, trueY + size, trueZ + size);
    a = glm::vec3(trueX + size, trueY + size, trueZ);
    addQuadToVbo(vbo, vertexIndex, a, b, c, d, type);
    // XZ
    a = glm::vec3(trueX, trueY, trueZ);
    b = glm::vec3(trueX + size, trueY, trueZ);
    c = glm::vec3(trueX + size, trueY, trueZ + size);
    d = glm::vec3(trueX, trueY, trueZ + size);
    addQuadToVbo(vbo, vertexIndex, a, b, c, d, type);

    if(cubes[position.x][position.y][position.z].isOpaque())
    {
        // YZ

        a = glm::vec3(trueX + size, trueY, trueZ);
        b = glm::vec3(trueX + size, trueY + size, trueZ);
        c = glm::vec3(trueX + size, trueY + size, trueZ + size);
        d = glm::vec3(trueX + size, trueY, trueZ + size);
        addQuadToVbo(vbo, vertexIndex, a, b, c, d, type);
        b = glm::vec3(trueX, trueY, trueZ);
        c = glm::vec3(trueX, trueY, trueZ + size);
        d = glm::vec3(trueX, trueY + size, trueZ + size);
        a = glm::vec3(trueX, trueY + size, trueZ);
        addQuadToVbo(vbo, vertexIndex, a, b, c, d, type);

        // XY
        a = glm::vec3(trueX, trueY, trueZ + size);
        b = glm::vec3(trueX + size, trueY, trueZ + size);
        c = glm::vec3(trueX + size, trueY + size, trueZ + size);
        d = glm::vec3(trueX, trueY + size, trueZ + size);
        addQuadToVbo(vbo, vertexIndex, a, b, c, d, type);
        b = glm::vec3(trueX, trueY, trueZ);
        c = glm::vec3(trueX, trueY + size, trueZ);
        d = glm::vec3(trueX + size, trueY + size, trueZ);
        a = glm::vec3(trueX + size, trueY, trueZ);
        addQuadToVbo(vbo, vertexIndex, a, b, c, d, type);
    }
}

void Chunk::countCube(unsigned int &transparent, unsigned int &opaque)
{
    for (int i = 0; i < CUBE_IN_CHUNK; ++i)
    {
        for (int j = 0; j < CUBE_IN_CHUNK; ++j)
        {
            for (int k = 0; k < CUBE_IN_CHUNK; ++k)
            {
                auto& c = cubes[i][j][k];
                if(c.getType() != Cube::CUBE_AIR)
                {
                    opaque += c.isOpaque() ? 1 : 0;
                    transparent += c.isTransparent() ? 1 : 0;
                }
            }
        }
    }
}

glm::vec2 Chunk::getAtlasPosition(float type)
{
    //grass	0 0
    //rock	1 0
    //dirt  3 0
    //water 14 0

    if(type == 1)
        return glm::vec2(0, 0);
    if (type == 2) //dirt
        return glm::vec2(2, 0);
    if (type == 4)
        return glm::vec2(1, 0);
    if (type == 5)
        return glm::vec2(14, 0);

    std::cout << "Error cube type not recognized " << std::endl;

    return glm::vec2(-1, -1);
}

void Chunk::initCubes()
{
    PerlinNoise p;
    p.setFreq(0.02f);
    for (int i = 0; i < CUBE_IN_CHUNK; ++i)
    {
        for (int j = 0; j < CUBE_IN_CHUNK; ++j)
        {
            for (int k = 0; k < CUBE_IN_CHUNK; ++k)
            {
                Cube::CubeType t = Cube::CUBE_AIR;
                float sample = p.sample(i, j, k);

                if(sample >= 0.5f)
                    t = Cube::CUBE_HERBE;
                else if(sample > 0.4f)
                    t = Cube::CUBE_EAU;


                cubes[i][j][k].setType(t);
            }
        }
    }

    toVbo();
}

Chunk::~Chunk()
{
    delete vboOpaque;
    delete vboTransparent;
}



