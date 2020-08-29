//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_GAMEOBJECT_HPP
#define DUMBERENGINE_GAMEOBJECT_HPP

#include "IComponent.hpp"
#include "Transform.hpp"
#include "../rendering/helper/Shader.hpp"
#include "physics/ICollisionCallbacks.hpp"
#include <list>
#include <string>

class GameObject : public IComponent, public ICollisionCallbacks
{
private:
    std::list<IComponent *> components;
    std::list<GuiComponent*> guiComponents;
    std::list<ICollisionCallbacks*> physicsCallback;
    
    Transform transform;
    bool isActive;

public:
    void onCollisionEnter(GameObject *other, glm::vec3 point) override;


public:

    std::string name;

    ~GameObject() override;

    GameObject(const char *name);

    void start() override;

    void update() override;

    void draw() override;
    void drawShadows(Shader *pShader);

    void drawInspector() override;

    void addComponent(IComponent *comp);

    Transform& getTransform() { return transform; }

    template<class T>
    T *getComponent()
    {
        auto ite = components.begin();

        while (ite != components.end())
        {
            T *comp = dynamic_cast<T *>(*ite);

            if (comp != nullptr)
            {
                return comp;
            }

            ite++;
        }

        return nullptr;
    }

    template<class T>
    void removeComponent()
    {
        auto ite = components.begin();

        while (ite != components.end())
        {
            T *type = dynamic_cast<T *>(*ite);

            if (type != nullptr)
            {
                components.remove(*ite);
                auto collisions = dynamic_cast<ICollisionCallbacks* >(*ite);
                if(collisions)
                {
                    physicsCallback.remove(collisions);
                }

                break;
            }

            ite++;
        }
    }
};

#endif //DUMBERENGINE_GAMEOBJECT_HPP
