//
// Created by fab on 27/02/2020.
//

#include "../../../headers/components/scripts/Chunk.hpp"
#include "../../../headers/utils/PerlinNoise.hpp"
#include "../../../headers/utils/BetterNoise.hpp"
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
    int transparentCubes = -1, opaqueCubes = -1;

    delete vboTransparent;
    delete vboOpaque;

    //we count the vertices
    foreachVisibleTriangle(true, &opaqueCubes, &transparentCubes, vboOpaque, vboTransparent);



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

    //we fill the vbos
    foreachVisibleTriangle(false, &opaqueCubes, &transparentCubes, vboOpaque, vboTransparent);


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
    BetterNoise p;
    p.setFreq(0.02f);
    for (int x = 0; x < CUBE_IN_CHUNK; ++x)
    {
        for (int y = 0; y < CUBE_IN_CHUNK; ++y)
        {
            for (int z = 0; z < CUBE_IN_CHUNK; ++z)
            {
                p.doPenaltyMiddle = true;
                p.setFreq(0.04f);
                float val = p.sample((float)x, (float)y, (float)z);
                p.doPenaltyMiddle = false;
                p.setFreq(0.2f);
                val -= (1.0f - max(val, p.sample((float)x, (float)y, (float)z))) / 20.0f;

                Cube& cube = cubes[x][y][z];

                if (val > 0.5f)
                    cube.setType(Cube::CUBE_HERBE);
                if (val > 0.51f)
                    cube.setType(Cube::CUBE_TERRE);
                if (val < 0.5 && z <= 0.1)
                    cube.setType(Cube::CUBE_EAU);
                if (val > 0.56)
                    cube.setType(Cube::CUBE_EAU);
            }
        }
    }
}

void Chunk::setNeighboors(Chunk *xPrev, Chunk *xNext, Chunk *yPrev, Chunk *yNext, Chunk *zPrev, Chunk *zNext)
{
    neighborhood[0] = xPrev;
    neighborhood[1] = xNext;
    neighborhood[2] = yPrev;
    neighborhood[3] = yNext;
    neighborhood[4] = zPrev;
    neighborhood[5] = zNext;
}

Chunk::~Chunk()
{
    delete vboOpaque;
    delete vboTransparent;
}

void Chunk::foreachVisibleTriangle(bool countOnly, int *nbVertOpaque, int *nbVertTrasp, Vbo *VboOpaque, Vbo *VboTrasparent)
{
    int type = 0;
    Cube * cube = nullptr;
    int nbVertices = 0;
    int iVerticeOpaque = 0;
    int iVerticeTransp = 0;
    int * iVertice = &iVerticeOpaque;
    //On parcourt tous nos cubes
    for (int x = 0; x < CUBE_IN_CHUNK; x++)
    {
        for (int y = 0; y < CUBE_IN_CHUNK; y++)
        {
            for (int z = 0; z < CUBE_IN_CHUNK; z++)
            {
                cube = &(cubes[x][y][z]);
                type = cube->getType();

                if (cube->getDraw() && type != Cube::CUBE_AIR)
                {
                    //Position du cube (coin bas gauche face avant)
                    float xPos = x * (float)Cube::CUBE_SIZE;
                    float yPos = y * (float)Cube::CUBE_SIZE;
                    float zPos = z * (float)Cube::CUBE_SIZE;

                    glm::vec3 a(xPos + Cube::CUBE_SIZE, yPos, zPos);
                    glm::vec3 b(xPos + Cube::CUBE_SIZE, yPos + Cube::CUBE_SIZE, zPos);
                    glm::vec3 c(xPos + Cube::CUBE_SIZE, yPos + Cube::CUBE_SIZE, zPos + Cube::CUBE_SIZE);
                    glm::vec3 d(xPos + Cube::CUBE_SIZE, yPos, zPos + Cube::CUBE_SIZE);
                    glm::vec3 e(xPos, yPos, zPos);
                    glm::vec3 f(xPos, yPos + Cube::CUBE_SIZE, zPos);
                    glm::vec3 g(xPos, yPos + Cube::CUBE_SIZE, zPos + Cube::CUBE_SIZE);
                    glm::vec3 h(xPos, yPos, zPos + Cube::CUBE_SIZE);

                    Cube * cubeXPrev = NULL;
                    Cube * cubeXNext = NULL;
                    Cube * cubeYPrev = NULL;
                    Cube * cubeYNext = NULL;
                    Cube * cubeZPrev = NULL;
                    Cube * cubeZNext = NULL;

                    get_surrounding_cubes(
                            x, y, z,
                            &cubeXPrev, &cubeXNext,
                            &cubeYPrev, &cubeYNext,
                            &cubeZPrev, &cubeZNext);

                    iVertice = &iVerticeTransp;
                    if (countOnly)
                        iVertice = nbVertTrasp;
                    Vbo * vbo = VboTrasparent;
                    if (cube->isOpaque()) {
                        iVertice = &iVerticeOpaque;
                        if (countOnly)
                            iVertice = nbVertOpaque;
                        vbo = VboOpaque;
                    }

                    //Premier QUAD (x+)
                    if (cubeXNext == NULL ||
                        (cube->isOpaque() && !cubeXNext->isOpaque()) || //Je suis un cube opaque et le cube a cote de moi est transparent
                        (!cube->isOpaque() && cubeXNext->getType() != type)) //Je suis un cube transparent et le cube a cote de moi est de l'air (on rend le transparent qu'au contact de l'air)
                    {
                        if (!countOnly)
                            addQuadToVbo(vbo, *iVertice, a, b, c, d, type); //x+
                        *iVertice += 6;
                    }

                    //Second QUAD (x-)
                    if (cubeXPrev == NULL ||
                        (cube->isOpaque() && !cubeXPrev->isOpaque()) || //Je suis un cube opaque et le cube a cote de moi est transparent
                        (!cube->isOpaque() && cubeXPrev->getType() != type)) //Je suis un cube transparent et le cube a cote de moi est de l'air (on rend le transparent qu'au contact de l'air)
                    {
                        if (!countOnly)
                            addQuadToVbo(vbo, *iVertice, f, e, h, g, type); //x-
                        *iVertice += 6;
                    }


                    //Troisieme QUAD (y+)
                    if (cubeYNext == NULL ||
                        (cube->isOpaque() && !cubeYNext->isOpaque()) || //Je suis un cube opaque et le cube a cote de moi est transparent
                        (!cube->isOpaque() && cubeYNext->getType() != type)) //Je suis un cube transparent et le cube a cote de moi est de l'air (on rend le transparent qu'au contact de l'air)
                    {
                        if (!countOnly)
                            addQuadToVbo(vbo, *iVertice, b, f, g, c, type); //y+
                        *iVertice += 6;
                    }

                    //Quatrieme QUAD (y-)
                    if (cubeYPrev == NULL ||
                        (cube->isOpaque() && !cubeYPrev->isOpaque()) || //Je suis un cube opaque et le cube a cote de moi est transparent
                        (!cube->isOpaque() && cubeYPrev->getType() != type)) //Je suis un cube transparent et le cube a cote de moi est de l'air (on rend le transparent qu'au contact de l'air)
                    {
                        if (!countOnly)
                            addQuadToVbo(vbo, *iVertice, e, a, d, h, type); //y-
                        *iVertice += 6;
                    }

                    //Cinquieme QUAD (z+)
                    if (cubeZNext == NULL ||
                        (cube->isOpaque() && !cubeZNext->isOpaque()) || //Je suis un cube opaque et le cube a cote de moi est transparent
                        (!cube->isOpaque() && cubeZNext->getType() != type)) //Je suis un cube transparent et le cube a cote de moi est de l'air (on rend le transparent qu'au contact de l'air)
                    {
                        if (!countOnly)
                            addQuadToVbo(vbo, *iVertice, c, g, h, d, type); //z+
                        *iVertice += 6;
                    }

                    //Sixième QUAD (le z-)
                    if (cubeZPrev == NULL ||
                        (cube->isOpaque() && !cubeZPrev->isOpaque()) || //Je suis un cube opaque et le cube a cote de moi est transparent
                        (!cube->isOpaque() && cubeZPrev->getType() != type)) //Je suis un cube transparent et le cube a cote de moi est de l'air (on rend le transparent qu'au contact d'un cube !=)
                    {
                        if (!countOnly)
                            addQuadToVbo(vbo, *iVertice, e, f, b, a, type); //z-
                        *iVertice += 6;
                    }
                }
            }
        }
    }
}

void Chunk::get_surrounding_cubes(int x, int y, int z, Cube **cubeXPrev, Cube **cubeXNext, Cube **cubeYPrev,
                                  Cube **cubeYNext, Cube **cubeZPrev, Cube **cubeZNext)
{
    *cubeXPrev = NULL;
    *cubeXNext = NULL;
    *cubeYPrev = NULL;
    *cubeYNext = NULL;
    *cubeZPrev = NULL;
    *cubeZNext = NULL;

    if (x == 0 && neighborhood[0] != NULL)
        *cubeXPrev = &(neighborhood[0]->cubes[CUBE_IN_CHUNK - 1][y][z]);
    else if (x > 0)
        *cubeXPrev = &(cubes[x - 1][y][z]);

    if (x == CUBE_IN_CHUNK - 1 && neighborhood[1] != NULL)
        *cubeXNext = &(neighborhood[1]->cubes[0][y][z]);
    else if (x < CUBE_IN_CHUNK - 1)
        *cubeXNext = &(cubes[x + 1][y][z]);

    if (y == 0 && neighborhood[2] != NULL)
        *cubeYPrev = &(neighborhood[2]->cubes[x][CUBE_IN_CHUNK - 1][z]);
    else if (y > 0)
        *cubeYPrev = &(cubes[x][y - 1][z]);

    if (y == CUBE_IN_CHUNK - 1 && neighborhood[3] != NULL)
        *cubeYNext = &(neighborhood[3]->cubes[x][0][z]);
    else if (y < CUBE_IN_CHUNK - 1)
        *cubeYNext = &(cubes[x][y + 1][z]);

    if (z == 0 && neighborhood[4] != NULL)
        *cubeZPrev = &(neighborhood[4]->cubes[x][y][CUBE_IN_CHUNK - 1]);
    else if (z > 0)
        *cubeZPrev = &(cubes[x][y][z - 1]);

    if (z == CUBE_IN_CHUNK - 1 && neighborhood[5] != NULL)
        *cubeZNext = &(neighborhood[5]->cubes[x][y][0]);
    else if (z < CUBE_IN_CHUNK - 1)
        *cubeZNext = &(cubes[x][y][z + 1]);
}

void Chunk::disableHiddenCubes()
{
    for(int x=0;x<CUBE_IN_CHUNK;x++)
        for(int y=0;y<CUBE_IN_CHUNK;y++)
            for(int z=0;z<CUBE_IN_CHUNK;z++)
            {
                cubes[x][y][z].setDraw(true);
                if(testHiddenCube(x, y, z))
                    cubes[x][y][z].setDraw(false);
            }
}

bool Chunk::testHiddenCube(int x, int y, int z)
{
    Cube * cubeXPrev = NULL;
    Cube * cubeXNext = NULL;
    Cube * cubeYPrev = NULL;
    Cube * cubeYNext = NULL;
    Cube * cubeZPrev = NULL;
    Cube * cubeZNext = NULL;

    if(x == 0 && neighborhood[0] != NULL)
        cubeXPrev = &(neighborhood[0]->cubes[CUBE_IN_CHUNK-1][y][z]);
    else if(x > 0)
        cubeXPrev = &(cubes[x-1][y][z]);

    if(x == CUBE_IN_CHUNK-1 && neighborhood[1] != NULL)
        cubeXNext = &(neighborhood[1]->cubes[0][y][z]);
    else if(x < CUBE_IN_CHUNK-1)
        cubeXNext = &(cubes[x+1][y][z]);

    if(y == 0 && neighborhood[2] != NULL)
        cubeYPrev = &(neighborhood[2]->cubes[x][CUBE_IN_CHUNK-1][z]);
    else if(y > 0)
        cubeYPrev = &(cubes[x][y-1][z]);

    if(y == CUBE_IN_CHUNK-1 && neighborhood[3] != NULL)
        cubeYNext = &(neighborhood[3]->cubes[x][0][z]);
    else if(y < CUBE_IN_CHUNK-1)
        cubeYNext = &(cubes[x][y+1][z]);

    if(z == 0 && neighborhood[4] != NULL)
        cubeZPrev = &(neighborhood[4]->cubes[x][y][CUBE_IN_CHUNK-1]);
    else if(z > 0)
        cubeZPrev = &(cubes[x][y][z-1]);

    if(z == CUBE_IN_CHUNK-1 && neighborhood[5] != NULL)
        cubeZNext = &(neighborhood[5]->cubes[x][y][0]);
    else if(z < CUBE_IN_CHUNK-1)
        cubeZNext = &(cubes[x][y][z+1]);

    if( cubeXPrev == NULL || cubeXNext == NULL ||
        cubeYPrev == NULL || cubeYNext == NULL ||
        cubeZPrev == NULL || cubeZNext == NULL )
        return false;

    return cubeXPrev->isOpaque() == true && //right
           cubeXNext->isOpaque() == true && //left
           cubeYPrev->isOpaque() == true && //up
           cubeYNext->isOpaque() == true && //down
           cubeZPrev->isOpaque() == true && //forward
           cubeZNext->isOpaque() == true;
}





