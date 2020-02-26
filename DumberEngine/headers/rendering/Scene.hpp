//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_SCENE_HPP
#define DUMBERENGINE_SCENE_HPP

#include <list>
#include "../components/GameObject.hpp"

class Scene : public IComponent
{
private:
    std::list<GameObject *> gameObjects;
public:
    Scene();

    void start() override;

    void update() override;

    void draw() override;

    void addGameObject(GameObject *go);

    void removeGameObject(std::string name);
};

#endif //DUMBERENGINE_SCENE_HPP
