//
// Created by fab on 25/02/2020.
//

#include <glm/vec3.hpp>
#include <glfw/glfw3.h>
#include "../../../headers/components/scripts/CameraScript.hpp"
#include "../../../headers/rendering/renderer/opengl/InputManager.hpp"
#include "../../../headers/rendering/helper/Time.hpp"

void CameraScript::start()
{

}

void CameraScript::update()
{
    auto &input = InputManager::getInstance();

    glm::vec3 movement = glm::vec3();

    if (input.isKeyPressed(GLFW_KEY_W))
    {
        movement.z += 2;
    } else if (input.isKeyPressed(GLFW_KEY_S))
    {
        movement.z -= 2;
    }
    if (input.isKeyPressed(GLFW_KEY_A))
    {
        movement.x -= 2;
    } else if (input.isKeyPressed(GLFW_KEY_D))
    {
        movement.x += 2;
    }

    if (input.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(renderer.GetHandle(), true);
    }

    if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
    {
        isCursorShown = !isCursorShown;
        glfwSetInputMode(renderer.GetHandle(), GLFW_CURSOR, isCursorShown ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
    }

    movement *= Time::getInstance().deltaTime;

    cam.move(movement);
    if (glfwGetInputMode(renderer.GetHandle(), GLFW_CURSOR) == GLFW_CURSOR_HIDDEN)
        cam.rotate(input.getMouseDelta());
}

void CameraScript::draw()
{

}

CameraScript::~CameraScript()
{
    delete cam;
}
