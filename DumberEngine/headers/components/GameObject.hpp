//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_GAMEOBJECT_HPP
#define DUMBERENGINE_GAMEOBJECT_HPP

#include "IComponent.hpp"
#include "Transform.hpp"
#include "../rendering/helper/Shader.hpp"
#include "physics/ICollisionCallbacks.hpp"
#include "rendering/IPostRendering.hpp"
#include "../rendering/Scene.hpp"
#include <list>
#include <string>
#include <vector>
#include <memory>

class GameObject : public IComponent, public ICollisionCallbacks
{
private:
    std::vector<IComponent *> components;
    std::vector<GuiComponent*> guiComponents;
    std::vector<ICollisionCallbacks*> physicsCallback;
    std::vector<IPostRendering*> postRenderers;
    
    std::shared_ptr<Transform> transform;
    bool isActive;
    bool hasPostRenderers;

public:
    void onCollisionEnter(GameObject *other, glm::vec3 point) override;

    static std::shared_ptr<GameObject> createGameObject(const char* name);

    GameObject();
    GameObject(const char *name);

public:

    std::string name;

    ~GameObject() override;

    void start() override;

    void update() override;

    void draw() override;
    void drawShadows(Shader *pShader);

    void drawInspector() override;
    void drawPostRenderers();

    void addComponent(IComponent* cmp);

    template<class T>
    T* addComponent()
    {
        T* comp = new T();

        *comp->gameObjectIndex = *gameObjectIndex;
        comp->transform = transform;

        components.push_back(comp);

        auto* collisions = dynamic_cast<ICollisionCallbacks*>(comp);

        if(collisions)
        {
            physicsCallback.push_back(collisions);
        }

        auto* postRenderer = dynamic_cast<IPostRendering*>(comp);
        if(postRenderer)
        {
            if(postRenderers.empty())
                hasPostRenderers = true;

            postRenderers.push_back(postRenderer);
        }

        comp->start();

        return comp;
    }

    std::shared_ptr<Transform> getTransform() { return transform; }

    template<class Archive>
    void serialize(Archive& archive)
    {

    }

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
