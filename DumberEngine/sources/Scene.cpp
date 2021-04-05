//
// Created by fab on 25/02/2020.
//

#include <imgui/imgui.h>
#include <ostream>
#include <fstream>
#include <cereal/types/memory.hpp>
#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/unordered_map.hpp>

#include "../headers/rendering/Scene.hpp"
#include "../headers/rendering/renderer/IWindow.h"

Scene* Scene::instance = nullptr;

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

    if(IWindow::instance->isForward())
    {
        while (iter != gameObjects.end())
        {
            (*iter).second->draw();
            ++iter;
        }
    }
    else
    {
        while (iter != gameObjects.end())
        {
            (*iter).second->geometryDraw(shaderGeometry);
            ++iter;
        }

       // glBindFramebuffer(GL_FRAMEBUFFER, 0);
        iter = gameObjects.begin();
        while (iter != gameObjects.end())
        {
            (*iter).second->lightingPass();
            ++iter;
        }
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

Scene::Scene() : shaderGeometry("shaders/deferred/cube/")
{
    //TODO: fix this ! We should not enable more instances
    instance = this;

    selectedGO = nullptr;
    indexCounter = 0;

    name.reserve(256);
}

void Scene::drawInspector()
{

    if(ImGui::Begin("Inspector"))
    {
        ImGui::Text("Scene name"); ImGui::SameLine();
        ImGui::InputText("", name.data(), 64); ImGui::SameLine();
        if(ImGui::Button("Save"))
        {
            save();
        }


        auto iter = gameObjects.begin();

        while (iter != gameObjects.end())
        {

            (*iter).second->drawInspector();
            ++iter;
        }


    }
    ImGui::End();
}

std::shared_ptr<GameObject> Scene::getGameObject(unsigned int index)
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

void Scene::save()
{
    std::string path(name);

    std::ofstream os(path + ".map");

    {
        cereal::PortableBinaryOutputArchive oArchive(os);

        oArchive(gameObjects);
    }
}

//TODO: simplify the use of this function

std::shared_ptr<GameObject> Scene::createGameObject(const char* nameGo)
{
    std::cout << "Creating " << nameGo << std::endl;

    std::pair<unsigned int, std::shared_ptr<GameObject>> pair;

    pair.first = indexCounter;
    pair.second = std::make_shared<GameObject>(nameGo);
    *pair.second->gameObjectIndex = indexCounter;

    indexCounter++;

    auto goIndex = gameObjects.insert(pair).first->first;
    toStart.push_back(gameObjects[goIndex].get());

    return gameObjects[goIndex];
}

