//
// Created by ELE5d5b9c842bce2 on 10/03/2020.
//

#ifndef DUMBERENGINE_ENGINE_HPP
#define DUMBERENGINE_ENGINE_HPP

#include "rendering/renderer/IWindow.h"
#include "rendering/Scene.hpp"
#include "systems/ISystem.hpp"
#include "rendering/renderer/IFbo.hpp"
#include "rendering/helper/Shader.hpp"
#include "debug/TextureDebug.hpp"

class Engine
{
private:
    IWindow* window;
    Scene* scene;

    std::vector<ISystem*> systems;

public:

    ~Engine();

    void start();
    void addSystem(ISystem* system)
    {
        system->init();
        systems.push_back(system);
    }
    void update();
};

#endif //DUMBERENGINE_ENGINE_HPP
