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

    inline EInputEvent toInputEvent(int event) override;

    inline void setKey(int code, EInputEvent event) override;

    inline bool isKeyPressed(int code) override;

    inline bool isKeyDown(int code) override;

    inline bool isMouseButtonPressed(int button) override;

    inline void setMouseVisible(bool isVisible) override;

    inline void setMousePosition(glm::vec2 position) override;

    inline void setMouseButton(int button, EInputEvent event) override;

    inline glm::vec2& getMouseDelta() override;

    inline glm::vec2& getMousePosition() override;

    void init() override;

    void update() override;
};

#endif //DUMBERENGINE_INPUTMANAGER_HPP
