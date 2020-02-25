//
// Created by fab on 24/02/2020.
//

#ifndef DUMBERENGINE_IINPUTMANAGER_HPP
#define DUMBERENGINE_IINPUTMANAGER_HPP

#include <glm/vec2.hpp>

class IInputManager
{
public:
    virtual bool isKeyPressed(int code) = 0;
    virtual bool isKeyDown(int code) = 0;

    virtual glm::vec2& getMousePosition() = 0;
    virtual glm::vec2& getMouseDelta() = 0;

};

#endif //DUMBERENGINE_IINPUTMANAGER_HPP
