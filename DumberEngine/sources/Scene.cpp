//
// Created by fab on 25/02/2020.
//

#include <imgui/imgui.h>
#include "../headers/rendering/Scene.hpp"

std::unordered_map<unsigned int, GameObject *> Scene::gameObjects;

void Scene::addGameObject(GameObject *go)
{
    std::pair<unsigned int, GameObject*> pair;

    pair.first = indexCounter++;
    pair.second = go;

    gameObjects.insert(pair);

    go->start();
}

void Scene::update()
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        (*iter).second->update();
        ++iter;
    }
}

void Scene::draw()
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        (*iter).second->draw();
        ++iter;
    }
}

void Scene::removeGameObject(std::string name)
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        if ((*iter).second->name == name)
        {
            gameObjects.erase(iter);
            break;
        }
        else
            ++iter;
    }
}

Scene::Scene()
{
    gameObjects = std::unordered_map<unsigned int, GameObject *>();
}

void Scene::drawInspector()
{

    if(ImGui::Begin("Inspector"))
    {
        auto iter = gameObjects.begin();

        while (iter != gameObjects.end())
        {

            (*iter).second->drawInspector();
            ++iter;
        }

        ImGui::End();
    }
}

GameObject *Scene::getGameObject(unsigned int index)
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        if((*iter).first == index)
            return (*iter).second;
    }

    return nullptr;
}

