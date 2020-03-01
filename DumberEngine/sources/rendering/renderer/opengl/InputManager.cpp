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

InputManager::InputManager()
{
    mousePosition = glm::vec2();
    memset(keys, 0, sizeof(void *) * GLFW_KEY_LAST);
    memset(mouseButtonState, 0, sizeof(void *) * GLFW_MOUSE_BUTTON_LAST);
}

void InputManager::keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    instance.keys[key] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

void InputManager::mouseButtonClicked(GLFWwindow *h, int button, int action, int mode)
{
    instance.mouseButtonState[button] = action == GLFW_PRESS || action == GLFW_REPEAT;
}

void InputManager::mouseMoved(GLFWwindow *, double xPos, double yPos)
{
    instance.mouseDelta.x = instance.mousePosition.x - xPos;
    instance.mouseDelta.y = instance.mousePosition.y - yPos;

    instance.mousePosition.x = xPos;
    instance.mousePosition.y = yPos;
}

bool InputManager::isMouseButtonPressed(int button)
{
    return mouseButtonState[button];
}

void InputManager::setMouseVisible(bool isVisible)
{
    isMouseShown = isVisible;
    glfwSetInputMode(renderer->getHandle(), GLFW_CURSOR, isMouseShown ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void InputManager::setMousePosition(glm::vec2 position)
{
    glfwSetCursorPos(renderer->getHandle(), position.x, position.y);

    mouseDelta = mousePosition - position;
    mousePosition = position;
}

glm::vec2 InputManager::getMouseDelta()
{
    return mouseDelta;
}



