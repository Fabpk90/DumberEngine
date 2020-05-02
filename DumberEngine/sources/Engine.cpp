//
// Created by ELE5d5b9c842bce2 on 10/03/2020.
//
#include <imgui/imgui.h>

#include "../headers/Engine.hpp"
#include "../headers/rendering/renderer/opengl/OpenGLRenderer.hpp"
#include "../headers/rendering/helper/Time.hpp"
#include "../headers/rendering/helper/Shader.hpp"
#include "../headers/systems/input/IInputManager.hpp"
#include "../headers/rendering/renderer/opengl/InputManager.hpp"
#include "../headers/components/scripts/CameraScript.hpp"
#include "../headers/components/scripts/World.hpp"

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>
#include <iostream>

#include "bullet/btBulletDynamicsCommon.h"
#include "../headers/rendering/renderer/opengl/Fbo.hpp"
#include "../headers/rendering/postprocess/PPOutline.hpp"
#include "../headers/components/scripts/Avatar.hpp"

static void loseFocus(bool isFocused)
{}

void Engine::start()
{
    SWindowData data{};
    data.width = 800;
    data.height = 600;
    data.name = "Dumber Engine";

    window = new OpenGLRenderer();
    window->init(data);
    window->setVSync(true);

    window->addWindowLoseFocusCallback(std::function(loseFocus));

    systems =  std::list<ISystem*>();

    InputManager* inputManager = new InputManager();
    inputManager->init();

    systems.push_front(inputManager);

    scene = new Scene();

    Camera* cam = new Camera();

    auto *o = new GameObject("Camera");
    o->addComponent(new CameraScript());

    auto* worldGO = new GameObject("World");
    World* world = new World();
    worldGO->addComponent(world);

    auto* avatarGO = new GameObject("Avatar");
    Avatar* avatar = new Avatar();
    avatar->setWorld(world);
    avatar->setCamera(cam);

    avatarGO->addComponent(avatar);

    scene->addGameObject(worldGO);
    scene->addGameObject(o);
    scene->addGameObject(avatarGO);

    //just for testing the bullet3 impl
    btBoxShape* box = new btBoxShape(btVector3(0, 1, 0));

    Camera::getInstance().pp.addPostProcess(new PPOutline("shaders/postprocess/Outline/"));
    Camera::getInstance().pp.addPostProcess(new PPOutline("shaders/postprocess/Blur/"));
    Camera::getInstance().pp.addPostProcess(new PPOutline("shaders/postprocess/GammaCorrection/", true));

    IFbo::shadowFBO = new Fbo(1024, 1024, true, false);
    IFbo::shadowFBO->setUpdateOnResize(true);
    IFbo::shadowFBO->bind();
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    IFbo::shadowFBO->unBind();

    shaderShadow = new Shader("shaders/shadow/");

    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);

    debug = new TextureDebug(IFbo::shadowFBO->getDepthTexture(), glm::vec2(0.5, 0.5));
}

void Engine::update()
{
    float lastFrame = 0;
    while (!glfwWindowShouldClose(window->getHandle()))
    {
        float currentFrame = glfwGetTime();
        Time::getInstance().deltaTime = currentFrame - lastFrame;
        Time::getInstance().time += Time::getInstance().deltaTime;
        lastFrame = currentFrame;

        if(IInputManager::instance->isKeyPressed(GLFW_KEY_F5))
        {
            Shader::reloadShaders();
        }

        scene->update();

        //shadow pass
        IFbo::shadowFBO->bind();
        glClear(GL_DEPTH_BUFFER_BIT);
        glDisable(GL_BLEND);

        glViewport(0, 0, IFbo::shadowFBO->getWidth(), IFbo::shadowFBO->getHeight());

        glEnable(GL_DEPTH_TEST);
        //glCullFace(GL_FRONT);


        shaderShadow->use();

        glm::mat4 lightProjection = glm::ortho(-64.0f, 64.0f, -64.0f, 64.0f, 1.f, 150.0f);
        glm::mat4 lightLookAt =  glm::lookAt((World::sunDirection),
                                             glm::vec3( 0.0f, 0.0f,  0.0f),
                                             glm::vec3( 0.0f, 1.0f,  0.0f));
        glm::mat4 lightVP = lightProjection * lightLookAt;
        shaderShadow->setMatrix4("lightSpaceMatrix", lightVP);

        scene->drawCastingShadowObjects(shaderShadow);


        glViewport(0, 0, IWindow::instance->getActualWidth(), IWindow::instance->getActualHeight());
        Camera::getInstance().pp.getFBO().bind();

        glClearColor(window->getClearColor().x, window->getClearColor().y, window->getClearColor().z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_BACK);

        scene->draw();
        //debug->draw();

        glDisable(GL_DEPTH_TEST);
        Camera::getInstance().pp.activateEffects();
        Camera::getInstance().pp.getFBO().unBind();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        Camera::getInstance().pp.draw();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
       // ImGui::ShowMetricsWindow();

        scene->drawInspector();

        Camera::getInstance().pp.drawInspector();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if(IInputManager::instance->isKeyPressed(GLFW_KEY_F2))
            Camera::getInstance().pp.getFBO().writeToDisk();

        for(ISystem* s : systems)
        {
            s->update();
        }

        glfwSwapBuffers(window->getHandle());
        glfwPollEvents();
    }
}

Engine::~Engine()
{
    for(ISystem* s : systems)
    {
        delete s;
    }

    delete scene;
    delete window;
}

