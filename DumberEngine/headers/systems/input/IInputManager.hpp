//
// Created by fab on 24/02/2020.
//

#ifndef DUMBERENGINE_IINPUTMANAGER_HPP
#define DUMBERENGINE_IINPUTMANAGER_HPP

#include <glm/vec2.hpp>
#include "../ISystem.hpp"
#include "../../rendering/renderer/IWindow.h"

class IInputManager : public ISystem
{
public:
    virtual bool isKeyPressed(int code) = 0;

    virtual bool isKeyDown(int code) = 0;

    virtual bool isMouseButtonPressed(int button) = 0;

    virtual void setMouseVisible(bool isVisible) = 0;
    virtual void setMousePosition(glm::vec2 position) = 0;
    virtual glm::vec2 getMouseDelta() = 0;

    virtual glm::vec2 &getMousePosition() = 0;

    static IInputManager* instance;
    IWindow *renderer;

    bool* keys;

    bool* mouseButtonState;

    bool isMouseShown;

    glm::vec2 mousePosition;
    glm::vec2 mouseDelta;
};

#endif //DUMBERENGINE_IINPUTMANAGER_HPP
