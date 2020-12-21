//
// Created by fab on 25/02/2020.
//

#include <imgui/imgui.h>
#include "../headers/rendering/Scene.hpp"

Scene* Scene::instance = nullptr;

void Scene::addGameObject(GameObject *go)
{
    std::pair<unsigned int, GameObject*> pair;

    pair.first = ++indexCounter;
    pair.second = go;

    *go->gameObjectIndex = indexCounter;

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
    //TODO: fix this ! We should not enable more instances
    instance = this;

    selectedGO = nullptr;
    indexCounter = 0;
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


    }
    ImGui::End();
}

GameObject *Scene::getGameObject(unsigned int index)
{
    return gameObjects.at(index);
}

void Scene::drawCastingShadowObjects(Shader *pShader)
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        (*iter).second->drawShadows(pShader);
        ++iter;
    }
}

void Scene::drawPostRendering()
{
    auto iter = gameObjects.begin();

    while (iter != gameObjects.end())
    {
        (*iter).second->drawPostRenderers();
        ++iter;
    }
}

