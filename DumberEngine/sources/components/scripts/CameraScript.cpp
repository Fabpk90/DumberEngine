//
// Created by fab on 25/02/2020.
//

#include <glm/vec3.hpp>
#include <glfw/glfw3.h>
#include <iostream>
#include "../../../headers/components/scripts/CameraScript.hpp"
#include "../../../headers/rendering/renderer/opengl/InputManager.hpp"
#include "../../../headers/rendering/helper/Time.hpp"

void CameraScript::start()
{

}

void CameraScript::update()
{
    auto &cam = (Camera::getInstance());
    auto &input = InputManager::getInstance();

    glm::vec3 movement = glm::vec3();

    if (input.isKeyPressed(GLFW_KEY_W))
    {
        movement.z += 2;
    }
    else if (input.isKeyPressed(GLFW_KEY_S))
    {
        movement.z -= 2;
    }
    if (input.isKeyPressed(GLFW_KEY_A))
    {
        movement.x -= 2;
    }
    else if (input.isKeyPressed(GLFW_KEY_D))
    {
        movement.x += 2;
    }

    if (input.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        input.renderer->closeWindow();
    }

    if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT) && isRightButtonReleased)
    {
        isRightButtonReleased = false;
        isCursorvisible = !isCursorvisible;
        input.setMouseVisible(isCursorvisible);
        //std::cout << "pressed " << std::endl;
    }
    else
    {
        //std::cout << "released " << std::endl;
        isRightButtonReleased = true;
    }

    movement *= Time::getInstance().deltaTime;

    cam.move(movement);
    if (!isCursorvisible)
        cam.rotate(input.getMouseDelta());
}

void CameraScript::draw()
{

}

CameraScript::CameraScript()
{
    //TODO: add a better way to handle the camera
    isRightButtonReleased = false;
    isCursorvisible = true;
}

CameraScript::~CameraScript()
{

}
