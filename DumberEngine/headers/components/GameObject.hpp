//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_GAMEOBJECT_HPP
#define DUMBERENGINE_GAMEOBJECT_HPP

#include "IComponent.hpp"
#include <list>
#include <string>

class GameObject : public IComponent
{
private:
    std::list<IComponent *> components;
    std::string name;
public:

    ~GameObject();

    GameObject(const char *name);

    void start() override;

    void update() override;

    void draw() override;

    void addComponent(IComponent *comp);


    template<class T>
    T *getComponent();

    template<class T>
    void removeComponent();
};

#endif //DUMBERENGINE_GAMEOBJECT_HPP
