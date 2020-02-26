//
// Created by fab on 25/02/2020.
//

#include "../headers/rendering/Scene.hpp"

void Scene::addGameObject(GameObject *go)
{
    gameObjects.push_back(go);

    go->start();
}

void Scene::start()
{

}

void Scene::update()
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        (*iter)->update();
        ++iter;
    }
}

void Scene::draw()
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        (*iter)->draw();
        ++iter;
    }
}

void Scene::removeGameObject(std::string name)
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        if ((*iter)->name == name)
        {
            gameObjects.remove(*iter);
            break;
        }
        else
            ++iter;
    }
}

Scene::Scene()
{
    gameObjects = std::list<GameObject *>();
}

