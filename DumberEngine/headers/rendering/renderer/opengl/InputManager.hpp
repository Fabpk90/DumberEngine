//
// Created by fab on 24/02/2020.
//

#ifndef DUMBERENGINE_INPUTMANAGER_HPP
#define DUMBERENGINE_INPUTMANAGER_HPP

#include "../../../systems/input/IInputManager.hpp"
#include "../IWindow.h"

class InputManager : public IInputManager
{
public:
    ~InputManager();

    InputManager();
    InputManager(const InputManager &) = delete;

    static void keyPressed(GLFWwindow *window, int key, int scancode, int action, int mods);

    static void mouseMoved(GLFWwindow *, double xPos, double yPos);

    static void mouseButtonClicked(GLFWwindow *, int button, int action, int mods);

    EInputEvent toInputEvent(int event) override;

    void setKey(int code, EInputEvent event) override;

    bool isKeyPressed(int code) override;

    bool isKeyDown(int code) override;

    bool isMouseButtonPressed(int button) override;

    void setMouseVisible(bool isVisible) override;

    void setMousePosition(glm::vec2 position) override;

    void setMouseButton(int button, EInputEvent event) override;

    glm::vec2 getMouseDelta() override;

    glm::vec2 &getMousePosition() override;

    void init() override;

    void update() override;
};

#endif //DUMBERENGINE_INPUTMANAGER_HPP
