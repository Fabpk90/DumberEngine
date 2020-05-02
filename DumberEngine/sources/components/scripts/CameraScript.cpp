//
// Created by fab on 25/02/2020.
//

#include <glm/vec3.hpp>
#include <glfw/glfw3.h>
#include <iostream>
#include <imgui/imgui.h>
#include "../../../headers/components/scripts/CameraScript.hpp"
#include "../../../headers/rendering/renderer/opengl/InputManager.hpp"
#include "../../../headers/rendering/helper/Time.hpp"

void CameraScript::start()
{
    auto &cam = (Camera::getInstance());
    isControllingMovement = false;
    cam.moveWorld(glm::vec3(0, 0, -2));
}

void CameraScript::update()
{
    auto &cam = (Camera::getInstance());
    auto &input = *InputManager::instance;

    glm::vec3 movement = glm::vec3();

    if(isControllingMovement)
    {
        if (input.isKeyDown(GLFW_KEY_W))
        {
            movement.z += 2;
        }
        else if (input.isKeyDown(GLFW_KEY_S))
        {
            movement.z -= 2;
        }
        if (input.isKeyDown(GLFW_KEY_A))
        {
            movement.x -= 2;
        }
        else if (input.isKeyDown(GLFW_KEY_D))
        {
            movement.x += 2;
        }

        if(input.isKeyDown(GLFW_KEY_LEFT_SHIFT))
            movement *= 2.0f;

        if(input.isKeyDown(GLFW_KEY_SPACE))
        {
            glm::vec3 up = glm::vec3(0, 3, 0);

            up *= Time::getInstance().deltaTime;

            cam.moveWorld(up);
        }
    }

    if (input.isKeyDown(GLFW_KEY_ESCAPE))
    {
        IWindow::instance->closeWindow();
    }

    input.setMouseVisible(true);

    if (input.isMouseButtonPressed(GLFW_MOUSE_BUTTON_RIGHT))
    {
        isCursorvisible = false;
        input.setMouseVisible(false);
    }
    else
    {
        isCursorvisible = true;
    }

    movement *= Time::getInstance().deltaTime;

    cam.move(movement);
    if (!isCursorvisible)
    {
        glm::vec2 delta, center;
        center = glm::vec2(IWindow::instance->getActualWidth() >> 1, IWindow::instance->getActualHeight() >> 1);

        delta = input.getMousePosition() - center;

        cam.rotate(delta / 4.0f);
        input.setMousePosition(center);
    }

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

void CameraScript::drawInspector()
{
    ImGui::Text("CameraScript");
    ImGui::Text("%f %f %f", Camera::getInstance().position.x, Camera::getInstance().position.y, Camera::getInstance().position.z);
    ImGui::Checkbox("is controlling movement ?", &isControllingMovement);
}
