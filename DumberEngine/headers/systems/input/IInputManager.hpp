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
protected:
    bool* keysDown;
    bool* keysPressed;

    bool* mouseButtonState;

    bool isMouseShown;

    glm::vec2 mousePosition;
    glm::vec2 mouseDelta;

public:
    enum EInputEvent
    {
        PRESSED,
        RELEASED,
        REPEAT,
        UNKNOWN
    };

    virtual ~IInputManager() = default;

    virtual EInputEvent toInputEvent(int event) = 0;

    virtual bool isKeyPressed(int code) = 0;

    virtual bool isKeyDown(int code) = 0;

    virtual bool isMouseButtonPressed(int button) = 0;

    virtual void setKey(int code, EInputEvent event) = 0;

    virtual void setMouseVisible(bool isVisible) = 0;
    virtual void setMousePosition(glm::vec2 position) = 0;
    virtual void setMouseButton(int button, EInputEvent event) = 0;


    virtual glm::vec2 getMouseDelta() = 0;

    virtual glm::vec2 &getMousePosition() = 0;

    static IInputManager* instance;
};

#endif //DUMBERENGINE_IINPUTMANAGER_HPP
