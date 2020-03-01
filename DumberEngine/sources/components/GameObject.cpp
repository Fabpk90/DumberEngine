//
// Created by fab on 25/02/2020.
//



#include "../../headers/components/GameObject.hpp"


GameObject::GameObject(const char *name) : name(name)
{
    components = std::list<IComponent *>();
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
    auto ite = components.begin();

    while (ite != components.end())
    {
        (*ite)->start();
        ++ite;
    }

}

void GameObject::update()
{
    auto ite = components.begin();

    while (ite != components.end())
    {
        (*ite)->update();
        ++ite;
    }
}

void GameObject::draw()
{
    auto ite = components.begin();

    while (ite != components.end())
    {
        (*ite)->draw();
        ++ite;
    }
}

void GameObject::addComponent(IComponent *comp)
{
    comp->gameObject = this;
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
    for (IComponent *i : components)
    {
        i->drawInspector();
    }
}
