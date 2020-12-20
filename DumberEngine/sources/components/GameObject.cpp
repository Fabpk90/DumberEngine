//
// Created by fab on 25/02/2020.
//

#include <imgui/imgui.h>
#include "../../headers/components/GameObject.hpp"


GameObject::GameObject(const char *name) : name(name)
{
    isActive = true;
    transform = Transform();

    guiComponents.push_back(&transform);
}

void GameObject::start()
{
    if(isActive)
    {
        auto ite = components.begin();

        while (ite != components.end())
        {
            (*ite)->start();
            ++ite;
        }
    }
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

void GameObject::addComponent(IComponent *comp)
{
    comp->gameObjectIndex = gameObjectIndex;
    comp->transform = &transform;

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
}

GameObject::~GameObject()
{
    for (IComponent *i : components)
    {
        delete i;
    }
}

void GameObject::drawInspector()
{
    if(ImGui::CollapsingHeader(name.c_str()))
    {
        ImGui::PushID(this);
        ImGui::Checkbox("Activate", &isActive);

        transform.drawInspector();

        for (IComponent *i : components)
        {
            i->drawInspector();
        }

        ImGui::PopID();
    }
}

void GameObject::drawShadows(Shader *pShader)
{
    for (IComponent *i : components)
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
