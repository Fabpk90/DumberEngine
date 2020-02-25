//
// Created by fab on 24/02/2020.
//

#include <glfw/glfw3.h>
#include <iostream>
#include "../../../../headers/rendering/renderer/opengl/InputManager.hpp"

InputManager InputManager::instance;

bool InputManager::isKeyPressed(int code)
{
    return keys[code];
}

bool InputManager::isKeyDown(int code)
{

    //TODO: handle this -> repeat
    return false;
}

glm::vec2 &InputManager::getMousePosition()
{
    return mousePosition;
}

glm::vec2 &InputManager::getMouseDelta()
{
    return mouseDelta;
}

InputManager::InputManager()
{
    mouseDelta = mousePosition = glm::vec2();
    memset(keys, 0, sizeof(void *) * GLFW_KEY_LAST);
}

void InputManager::keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    InputManager::getInstance().keys[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

void InputManager::mouseMoved(GLFWwindow *window, double xpos, double ypos)
{
    auto &instance = InputManager::getInstance();

    instance.mouseDelta.x = instance.mousePosition.x - xpos;
    instance.mouseDelta.y = instance.mousePosition.y - ypos;

    instance.mousePosition.x = xpos;
    instance.mousePosition.y = ypos;
}

void InputManager::mouseButtonClicked(GLFWwindow *h, int button, int action, int mode)
{
    InputManager::getInstance().mouseButtonState[button] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

bool InputManager::isMouseButtonPressed(int button)
{
    return mouseButtonState[button];
}

void InputManager::setMouseVisible(bool isVisible)
{
    isMouseShown = isVisible;
    glfwSetInputMode()
}

