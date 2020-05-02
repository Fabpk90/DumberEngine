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

    std::list<ISystem*> systems;

    GLuint colorBuffer;

public:

    ~Engine();

    void start();
    void update();
};

#endif //DUMBERENGINE_ENGINE_HPP
