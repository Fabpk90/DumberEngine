//
// Created by fab on 24/02/2020.
//

#ifndef DUMBERENGINE_INPUTMANAGER_HPP
#define DUMBERENGINE_INPUTMANAGER_HPP

#include "../../../systems/input/IInputManager.hpp"
#include "../IWindow.h"

class InputManager : public IInputManager
{
private:
    bool keys[GLFW_KEY_LAST];

    bool mouseButtonState[GLFW_MOUSE_BUTTON_LAST];

    bool isMouseShown;

    glm::vec2 mousePosition;
    glm::vec2 mouseDelta;

public:

    InputManager(const InputManager &) = delete;

    static void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void mouseMoved(GLFWwindow *, double xPos, double yPos);

    static void mouseButtonClicked(GLFWwindow *, int button, int action, int mods);

    bool isKeyPressed(int code) override;

    bool isKeyDown(int code) override;

    bool isMouseButtonPressed(int button) override;

    void setMouseVisible(bool isVisible) override;

    void setMousePosition(glm::vec2 position) override;

    glm::vec2 getMouseDelta() override;

    glm::vec2 &getMousePosition() override;

    void init() override;

    void update() override;

    void destroy() override;

    InputManager();
};

#endif //DUMBERENGINE_INPUTMANAGER_HPP
