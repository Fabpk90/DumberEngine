//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_ICOMPONENT_HPP
#define DUMBERENGINE_ICOMPONENT_HPP

#include "GuiComponent.hpp"
#include "../rendering/helper/Shader.hpp"
#include "Transform.hpp"

class IComponent : public GuiComponent
{
public:

    IComponent()
    {
        gameObjectIndex = new unsigned int;
    }

    virtual void start(){};

    virtual void update(){};

    virtual void draw(){};

    virtual ~IComponent()
    {
        delete gameObjectIndex;
    };

    IComponent(IComponent&& c)
    {
        transform = c.transform;
        gameObjectIndex = c.gameObjectIndex;

        c.transform = nullptr;
        c.gameObjectIndex = nullptr;
    };

    IComponent(const IComponent& c)
    {
        transform = c.transform;
        gameObjectIndex = c.gameObjectIndex;
    };



    virtual bool castShadow() { return false; }
    virtual void drawShadow(Shader *pShader)
    {};

    virtual void drawInspector() override
    {};

public:
    unsigned int* gameObjectIndex;
    Transform* transform;
};

#endif //DUMBERENGINE_ICOMPONENT_HPP
