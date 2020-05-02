//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_ICOMPONENT_HPP
#define DUMBERENGINE_ICOMPONENT_HPP

#include "GuiComponent.hpp"
#include "../rendering/helper/Shader.hpp"

class IComponent : public GuiComponent
{
public:
    virtual void start() = 0;

    virtual void update() = 0;

    virtual void draw() = 0;

    virtual ~IComponent()
    {};

    virtual bool castShadow() { return false; }
    virtual void drawShadow(Shader *pShader)
    {};

public:
    unsigned int gameObjectIndex;
};

#endif //DUMBERENGINE_ICOMPONENT_HPP
