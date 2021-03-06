//
// Created by fab on 24/02/2020.
//

#include <glfw/glfw3.h>
#include <iostream>
#include "../../../../headers/rendering/renderer/opengl/InputManager.hpp"

bool InputManager::isKeyPressed(int code)
{
    return keysPressed[code];
}

bool InputManager::isKeyDown(int code)
{
    return keysDown[code];
}

glm::vec2 &InputManager::getMousePosition()
{
    return mousePosition;
}

InputManager::InputManager()
{
    instance = this;
}

void InputManager::keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    instance->setKey(key, instance->toInputEvent(action));
}

void InputManager::mouseButtonClicked(GLFWwindow *h, int button, int action, int mode)
{
    instance->setMouseButton(button, instance->toInputEvent(action));
}

void InputManager::mouseMoved(GLFWwindow *, double xPos, double yPos)
{
    instance->setMousePosition(glm::vec2(xPos, yPos));
}

bool InputManager::isMouseButtonPressed(int button)
{
    return mouseButtonState[button];
}

void InputManager::setMouseVisible(bool isVisible)
{
    isMouseShown = isVisible;
    glfwSetInputMode(IWindow::instance->getHandle(), GLFW_CURSOR, isMouseShown ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_HIDDEN);
}

void InputManager::setMousePosition(glm::vec2 position)
{
    glfwSetCursorPos(IWindow::instance->getHandle(), position.x, position.y);

    mouseDelta = mousePosition - position;
    mousePosition = position;
}

glm::vec2& InputManager::getMouseDelta()
{
    return mouseDelta;
}

void InputManager::init()
{
    std::cout << "Initializing the Input Manager" << std::endl;
    mousePosition = glm::vec2();

    keysDown = new bool[GLFW_KEY_LAST];
    keysPressed = new bool[GLFW_KEY_LAST];
    mouseButtonState = new bool[GLFW_MOUSE_BUTTON_LAST];

    memset(keysDown, 0, sizeof(bool) * GLFW_KEY_LAST);
    memset(keysPressed, 0, sizeof(bool) * GLFW_KEY_LAST);
    memset(mouseButtonState, 0, sizeof(bool) * GLFW_MOUSE_BUTTON_LAST);


    std::cout << "Initialized the Input Manager" << std::endl;
}

void InputManager::update()
{
   memset(keysPressed, 0, sizeof(bool) * GLFW_KEY_LAST);
}

IInputManager::EInputEvent InputManager::toInputEvent(int event)
{
    switch (event)
    {
        case GLFW_PRESS:
            return PRESSED;
        case GLFW_REPEAT:
            return REPEAT;
        case GLFW_RELEASE:
            return RELEASED;
        default:
            return UNKNOWN;
    }
}

void InputManager::setKey(int code, IInputManager::EInputEvent event)
{
    //TODO: handle key down/pressed (one shot)
    switch (event)
    {
        case PRESSED:
            keysDown[code] = true;
            keysPressed[code] = true;
            break;
        case RELEASED:
            keysDown[code] = false;
            keysPressed[code] = false;
            break;
        case REPEAT:
            keysDown[code] = true;
            keysPressed[code] = false;
            break;
        case UNKNOWN:
            break;
    }
}

void InputManager::setMouseButton(int button, IInputManager::EInputEvent event)
{
    mouseButtonState[button] = event == PRESSED || event == REPEAT;
}

InputManager::~InputManager()
{
    delete[] keysDown;
    delete[] keysPressed;
    delete[] mouseButtonState;
}



