//
// Created by fab on 28/04/2020.
//

#include <iostream>
#include "../../../headers/components/scripts/Avatar.hpp"
#include "../../../headers/utils/Physics.hpp"
#include "../../../headers/rendering/renderer/opengl/InputManager.hpp"

void Avatar::drawInspector()
{

}

void Avatar::start()
{
    height = 1.8f;
    currentHeight = height;
    width = 0.5f;
    forward = false;
    backward = false;
    left = false;
    right = false;
    standing = false;
    jump = false;
    inWater = false;
    crouch = false;
    run = false;

    mass = 75.0f;

    gravity = glm::vec3(0, -1, 0) * 9.81f;
    damping = glm::vec3(1, 1, 1);
}

void Avatar::update()
{
    auto& input = InputManager::instance;

    if(input->isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
    {
        rayCast();
    }

    position = cam->position;
}

void Avatar::draw()
{

}

void Avatar::rayCast()
{
    startPositionRayCast = cam->position;
    endPositionRayCast = (startPositionRayCast + cam->direction * 5.0f);

    int xAvatar, yAvatar, zAvatar;

    xAvatar = position.x / Chunk::CUBE_IN_CHUNK;
    yAvatar = position.y / Chunk::CUBE_IN_CHUNK;
    zAvatar = position.z / Chunk::CUBE_IN_CHUNK;

    Chunk* chunk = world->getChunkAt(xAvatar, yAvatar, zAvatar);

    if(chunk != nullptr) // if in a chunk
    {
        int xDeb = ( (int)position.x % Chunk::CUBE_IN_CHUNK ) - 1;
        int yDeb = ((int)position.y % Chunk::CUBE_IN_CHUNK) - 1;
        int zDeb = ((int)position.z % Chunk::CUBE_IN_CHUNK) - 1;

        if (xDeb < 0)
            xDeb = 0;
        if (yDeb < 0)
            yDeb = 0;
        if (zDeb < 0)
            zDeb = 0;

        int xFin = ((int)position.x % Chunk::CUBE_IN_CHUNK) + maxRaycastDistance;
        int yFin = ((int)position.y % Chunk::CUBE_IN_CHUNK) + maxRaycastDistance;
        int zFin = ((int)position.z % Chunk::CUBE_IN_CHUNK) + maxRaycastDistance;

        //todo: discard cube that the avatar is not facing towards

        const int size = Cube::CUBE_SIZE;
        for (int x = xDeb; x <= xFin; x++)
            for (int y = yDeb; y <= yFin; y++)
                for (int z = zDeb; z <= zFin; z++)
                {
                    Cube* cube = chunk->getCubeAt(x, y, z);

                    if(cube != nullptr)
                    {
                        if (cube->isSolid())
                        {
                            //Check for the faces

                            const int trueX = (x * size);
                            const int trueY = (y * size);
                            const int trueZ = (z * size);

                            //Face 1
                            glm::vec3 a = glm::vec3(trueX, trueY, trueZ + size);
                            glm::vec3 b = glm::vec3(trueX + size, trueY, trueZ + size);
                            glm::vec3 c = glm::vec3(trueX + size, trueY + size, trueZ + size);
                            glm::vec3 d = glm::vec3(trueX, trueY + size, trueZ + size);

                            if (Physics::isIntersectingTriangle(startPositionRayCast, endPositionRayCast, a, b, c, d))
                            {
                                world->deleteCube(x, y, z);
                                break;
                            }

                            b = glm::vec3(trueX, trueY, trueZ);
                            c = glm::vec3(trueX, trueY + size, trueZ);
                            d = glm::vec3(trueX + size, trueY + size, trueZ);
                            a = glm::vec3(trueX + size, trueY, trueZ);

                            if (Physics::isIntersectingTriangle(startPositionRayCast, endPositionRayCast, a, b, c, d))
                            {
                                world->deleteCube(x, y, z);
                                break;
                            }

                            // XZ
                            a = glm::vec3(trueX, trueY, trueZ);
                            b = glm::vec3(trueX + size, trueY, trueZ);
                            c = glm::vec3(trueX + size, trueY, trueZ + size);
                            d = glm::vec3(trueX, trueY, trueZ + size);

                            if (Physics::isIntersectingTriangle(startPositionRayCast, endPositionRayCast, a, b, c, d))
                            {
                                world->deleteCube(x, y, z);
                                break;
                            }

                            b = glm::vec3(trueX, trueY + size, trueZ);
                            c = glm::vec3(trueX, trueY + size, trueZ + size);
                            d = glm::vec3(trueX + size, trueY + size, trueZ + size);
                            a = glm::vec3(trueX + size, trueY + size, trueZ);

                            if (Physics::isIntersectingTriangle(startPositionRayCast, endPositionRayCast, a, b, c, d))
                            {
                                world->deleteCube(x, y, z);
                                break;
                            }

                            // YZ
                            b = glm::vec3(trueX, trueY, trueZ);
                            c = glm::vec3(trueX, trueY, trueZ + size);
                            d = glm::vec3(trueX, trueY + size, trueZ + size);
                            a = glm::vec3(trueX, trueY + size, trueZ);

                            if (Physics::isIntersectingTriangle(startPositionRayCast, endPositionRayCast, a, b, c, d))
                            {
                                world->deleteCube(x, y, z);
                                break;
                            }

                            a = glm::vec3(trueX + size, trueY, trueZ);
                            b = glm::vec3(trueX + size, trueY + size, trueZ);
                            c = glm::vec3(trueX + size, trueY + size, trueZ + size);
                            d = glm::vec3(trueX + size, trueY, trueZ + size);

                            if (Physics::isIntersectingTriangle(startPositionRayCast, endPositionRayCast, a, b, c, d))
                            {
                                world->deleteCube(x, y, z);
                                break;
                            }
                        }

                    }
                }
    }
}

void Avatar::setCamera(Camera *pCamera)
{
    cam = pCamera;
}
