//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_ICOMPONENT_HPP
#define DUMBERENGINE_ICOMPONENT_HPP

#include "GuiComponent.hpp"
#include "../rendering/helper/Shader.hpp"
#include "Transform.hpp"

#include <memory>

class IComponent : public GuiComponent
{
public:

    IComponent()
    {
        gameObjectIndex = std::make_shared<unsigned int>();
    }

    virtual void start(){};

    virtual void update(){};

    virtual void fillGBuffer(Shader &shader)
    {};
    virtual void draw(){};

    IComponent(IComponent&& c)
    {
        transform = std::move(c.transform);
        gameObjectIndex = std::move(c.gameObjectIndex);

        c.transform = nullptr;
        c.gameObjectIndex = nullptr;
    };

    IComponent(const IComponent& c)
    {
        transform = std::shared_ptr<Transform>(c.transform.get());
        gameObjectIndex = std::shared_ptr<unsigned int>(c.gameObjectIndex);
    };

    template<class Archive>
    void serialize(Archive& ar)
    {
        ar(gameObjectIndex);
    }

    virtual bool castShadow() { return false; }
    virtual void drawShadow(Shader *pShader)
    {};

    virtual void drawInspector() override
    {};

public:
    std::shared_ptr<unsigned int> gameObjectIndex;
    std::shared_ptr<Transform> transform;
};

#endif //DUMBERENGINE_ICOMPONENT_HPP
