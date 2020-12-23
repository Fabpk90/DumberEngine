//
// Created by fab on 25/02/2020.
//

#include <imgui/imgui.h>
#include "../../headers/components/GameObject.hpp"

GameObject::GameObject()
{
    isActive = true;

    guiComponents.push_back(transform.get());
}

GameObject::GameObject(const char *name) : name(name), IComponent()
{
    isActive = true;

    guiComponents.push_back(transform.get());
    transform = std::make_shared<Transform>();
}

void GameObject::start()
{

}

void GameObject::update()
{
    if(isActive)
    {
        auto ite = components.begin();

        while (ite != components.end())
        {
            (*ite)->update();
            ++ite;
        }
    }
}

void GameObject::draw()
{
    if(isActive)
    {
        auto ite = components.begin();

        while (ite != components.end())
        {
            (*ite)->draw();
            ++ite;
        }
    }
}



GameObject::~GameObject()
= default;

void GameObject::drawInspector()
{
    if(ImGui::CollapsingHeader(name.c_str()))
    {
        ImGui::PushID(this);
        ImGui::Checkbox("Activate", &isActive);

        transform->drawInspector();

        for (const auto& i : components)
        {
            i->drawInspector();
        }

        ImGui::PopID();
    }
}

void GameObject::drawShadows(Shader *pShader)
{
    for (const auto& i : components)
    {
        if(i->castShadow())
            i->drawShadow(pShader);
    }
}

void GameObject::onCollisionEnter(GameObject *other, glm::vec3 point)
{
    for(auto* callback : physicsCallback)
    {
        callback->onCollisionEnter(other, point);
    }
}

void GameObject::drawPostRenderers()
{
    if(!hasPostRenderers) return;

    for(auto* postRenderer : postRenderers)
        postRenderer->postDraw();

}

std::shared_ptr<GameObject> GameObject::createGameObject(const char *name)
{
    return Scene::instance->createGameObject(name);
}

void GameObject::addComponent(IComponent *comp)
{
    *comp->gameObjectIndex = *gameObjectIndex;
    comp->transform = transform;

    std::shared_ptr<IComponent> cmpShareable(comp);

    components.push_back(cmpShareable);

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

}
