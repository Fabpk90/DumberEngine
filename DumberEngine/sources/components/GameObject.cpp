//
// Created by fab on 25/02/2020.
//



#include <imgui/imgui.h>
#include "../../headers/components/GameObject.hpp"
#include "../../headers/rendering/helper/Shader.hpp"


GameObject::GameObject(const char *name) : name(name)
{
    isActive = true;
    components = std::list<IComponent *>();
    transform = Transform();
}


template<class T>
T *GameObject::getComponent()
{
    auto ite = components.begin();

    while (ite != components.end())
    {
        T *comp = dynamic_cast<T *>(*ite);

        if (comp != nullptr)
        {
            return comp;
        }
    }

    return nullptr;
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
    comp->gameObjectIndex = indexInScene;
    components.push_back(comp);
}

template<class T>
void GameObject::removeComponent()
{
    auto ite = components.begin();

    while (ite != components.end())
    {
        T *type = dynamic_cast<T *>(*ite);

        if (type != nullptr)
        {
            components.remove(*ite);
            break;
        }
        else
            ++ite;
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
        //TODO: optimize this
        ImGui::Checkbox(("Activate " + name).c_str(), &isActive);

        for (IComponent *i : components)
        {
            i->drawInspector();
        }
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
