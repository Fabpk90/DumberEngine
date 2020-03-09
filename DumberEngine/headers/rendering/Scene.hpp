//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_SCENE_HPP
#define DUMBERENGINE_SCENE_HPP

#include <unordered_map>
#include "../components/GameObject.hpp"

class Scene
{
private:
    static std::unordered_map<unsigned int, GameObject *> gameObjects;
    unsigned int indexCounter;

    GameObject* selectedGO;

public:
    Scene();

    void update();

    void draw();

    void addGameObject(GameObject *go);

    void removeGameObject(std::string name);

    void drawInspector();

     static GameObject* getGameObject(unsigned int index);
};

#endif //DUMBERENGINE_SCENE_HPP
