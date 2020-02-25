//
// Created by fab on 24/02/2020.
//

#ifndef DUMBERENGINE_INPUTMANAGER_HPP
#define DUMBERENGINE_INPUTMANAGER_HPP

#include "../IInputManager.hpp"

class InputManager : public IInputManager
{
private:
    bool keys[GLFW_KEY_LAST + 1];
    glm::vec2 mousePosition;
    glm::vec2 mouseDelta;
    InputManager();
    static InputManager instance;
public:

    InputManager(const InputManager& ) = delete;

    static InputManager& getInstance()
    {
        return instance;
    }

    static void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseMoved(GLFWwindow* window, double xpos, double ypos);


    bool isKeyPressed(int code) override;
    bool isKeyDown(int code) override;

    glm::vec2& getMousePosition() override;
    glm::vec2& getMouseDelta() override ;
};

#endif //DUMBERENGINE_INPUTMANAGER_HPP
