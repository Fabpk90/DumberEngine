//
// Created by fab on 28/04/2020.
//

#include <iostream>
#include "../../../headers/components/scripts/Avatar.hpp"
#include "../../../headers/utils/Physics.hpp"
#include "../../../headers/rendering/renderer/opengl/InputManager.hpp"
#include "../../../headers/rendering/helper/Time.hpp"
#include "../../../headers/utils/Utilities.hpp"

void Avatar::drawInspector()
{

}

void Avatar::start()
{
    position = glm::vec3(10, 80, 10);
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

    if (input->isKeyDown(GLFW_KEY_W))
    {
        forward = true;
    }
    else if (input->isKeyDown(GLFW_KEY_S))
    {
       backward = true;
    }
    if (input->isKeyDown(GLFW_KEY_A))
    {
       left = true;
    }
    else if (input->isKeyDown(GLFW_KEY_D))
    {
        right = true;
    }

    if (input->isKeyPressed(GLFW_KEY_SPACE))
    {
        jump = true;
    }

    float elapsed = Time::getInstance().deltaTime;

    //Par defaut, on applique la gravité (-100 sur Z), la moitie si dans l'eau
    glm::vec3 force = glm::vec3(0, -1, 0) * 9.81f;
    if (inWater)
        force = glm::vec3(0, -1, 0) * 0.5f;

    float lastheight = currentHeight;
    currentHeight = height;
    if (crouch)
        currentHeight = height / 2;

    //Pour ne pas s'enfoncer dans le sol en une frame quand on se releve
    if (currentHeight > lastheight)
        position.y += height / 4;

    float accel = 40;
    if (crouch)
        accel = 20;
    if (!standing)
        accel = 5;
    if (run)
        accel = 80;

    glm::vec3 forwardVector(cam->direction.x, 0, cam->direction.z);
    glm::vec3 rightVector(cam->right.x,0 ,  cam->right.z);

    //On applique les controles en fonction de l'accélération
    if (forward)
        force += forwardVector * accel;
    if (backward)
        force += forwardVector * -accel;
    if (left)
        force += rightVector * -accel;
    if (right)
        force += rightVector * accel;


    //On applique le jump
    if (jump)
    {
        force += glm::vec3(0, 1, 0) * 5.0f / elapsed; //(impulsion, pas fonction du temps)
        jump = false;
    }

    //On applique les forces en fonction du temps écoulé
    velocity += force * elapsed;

    //On met une limite a sa vitesse horizontale
    float speedmax = 70;
    if (crouch)
        speedmax = 45;
    if (!standing)
        speedmax = 70;
    if (run)
        speedmax = 140;

    glm::vec3 horSpeed = velocity;
    horSpeed.y = 0;
    if (horSpeed.length() > speedmax)
    {
        horSpeed = glm::normalize(horSpeed);
        horSpeed *= speedmax;
        velocity.x = horSpeed.x;
        velocity.z = horSpeed.z;
    }

    //On le déplace, en sauvegardant son ancienne position
    glm::vec3 oldPosition = position;
    position += (velocity * elapsed);

    //YLog::log(YLog::ENGINE_INFO, ("zS " + toString(Speed.Z)).c_str());

    if (_TimerStanding.getElapsedSeconds() > 0.01)
        standing = false;
    for (int pass = 0; pass < 2; pass++)
    {
        for (int i = 0; i < 6; i++)
        {
            float valueColMin = 0;
            World::MAxis axis = world->getMinCol(position, velocity, width, currentHeight, valueColMin, i < 3);
            if (axis != 0)
            {
                if (axis & World::AXIS_X)
                {
                    position.x += valueColMin + 0.001 * sign(valueColMin);
                    velocity.x = 0;
                }
                if (axis & World::AXIS_Y)
                {
                    position.y += valueColMin + 0.001 * sign(valueColMin);
                    velocity.y = 0;
                }
                if (axis & World::AXIS_Z)
                {
                    velocity.z = 0;
                    position.z += valueColMin + 0.001 * sign(valueColMin);
                    standing = true;
                    _TimerStanding.start();
                }
            }
        }
    }

    int x = (int)(position.x / Cube::CUBE_SIZE);
    int y = (int)(position.y / Cube::CUBE_SIZE);
    int z = (int)(position.z / Cube::CUBE_SIZE);


    //Si on est dans l'eau
    inWater = false;
    if (world->getCube(x, y, z) != nullptr &&
        world->getCube(x, y, z)->getType() == Cube::CUBE_EAU)
        inWater = true;

    if (inWater)
    {
        //Standing = true;
        velocity *= pow(0.2f, elapsed);
    }
    else if (standing)
        velocity *= pow(0.01f, elapsed);

    resetDirections();
    cam->setPosition(position + glm::vec3(0, currentHeight, 0));
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
