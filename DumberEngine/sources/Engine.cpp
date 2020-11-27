//
// Created by ELE5d5b9c842bce2 on 10/03/2020.
//
#include <glad/glad.h>
#include <imgui/imgui.h>

#include "../headers/Engine.hpp"
#include "../headers/rendering/renderer/opengl/OpenGLRenderer.hpp"
#include "../headers/rendering/helper/Time.hpp"
#include "../headers/systems/input/IInputManager.hpp"
#include "../headers/rendering/renderer/opengl/InputManager.hpp"
#include "../headers/components/scripts/CameraScript.hpp"
#include "../headers/components/scripts/World.hpp"

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include "../headers/rendering/postprocess/PPNoParams.hpp"
#include "../headers/components/scripts/Avatar.hpp"
#include "../headers/systems/rendering/ShadowMapping.hpp"
#include "../headers/systems/physics/Physics.hpp"
#include "../headers/components/physics/BoxCollider.hpp"
#include "../headers/components/physics/RigidBody.hpp"
#include "../headers/components/scripts/PhysicsTest.hpp"
#include "../headers/components/rendering/StaticMesh.hpp"
#include "../headers/systems/Editor.hpp"

static void loseFocus(bool isFocused)
{}

void Engine::start()
{
    SWindowData data{};
    data.width = 1280;
    data.height = 720;
    data.name = "Dumber Engine";

    window = new OpenGLRenderer();
    window->init(data);
    window->setVSync(true);

    window->addWindowLoseFocusCallback(std::function(loseFocus));

    addSystem(new InputManager());
    addSystem(new Physics());
    addSystem(new Editor());

    scene = new Scene();

    Camera* cam = new Camera();

    auto *o = new GameObject("Camera");
    o->addComponent(new CameraScript());

    auto* worldGO = new GameObject("World");
    World* world = new World();
    worldGO->addComponent(world);

    auto* avatarGO = new GameObject("Avatar");

    //Avatar* avatar = new Avatar();
    //avatar->setWorld(world);
   // avatar->setCamera(cam);

    avatarGO->addComponent(new CameraScript());

    auto* phy = new GameObject("RigidBody");
    phy->addComponent(new BoxCollider());
    phy->addComponent(new RigidBody());
    auto test = new PhysicsTest();
    test->test = "yeppa";
    phy->addComponent(test);

    auto* box = new GameObject("BoxCollider");
    box->addComponent(new BoxCollider());
    auto test1 = new PhysicsTest();
    test1->test = "nooope";
    box->addComponent(test1);

    auto meshGO = new GameObject("StaticMesh");
    auto sm = new StaticMesh();
    sm->loadFrom("mesh/Cerberus/Cerberus_LP.fbx");
    meshGO->addComponent(sm);

   // scene->addGameObject(worldGO);
    scene->addGameObject(o);
   // scene->addGameObject(avatarGO);
    //scene->addGameObject(phy);
   // scene->addGameObject(box);
    scene->addGameObject(meshGO);

    Camera::getInstance().pp.addPostProcess(new PPNoParams("shaders/postprocess/Outline/"));
    Camera::getInstance().pp.addPostProcess(new PPNoParams("shaders/postprocess/Blur/"));
    Camera::getInstance().pp.addPostProcess(new PPNoParams("shaders/postprocess/GammaCorrection/", true));

    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LEQUAL);
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
        ShadowMapping::getInstance()->draw();

        //post process
        Camera::getInstance().pp.getFBO().bind();
        glViewport(0, 0, IWindow::instance->getActualWidth(), IWindow::instance->getActualHeight());

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

        //GUI
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowMetricsWindow();

        scene->drawInspector();

        Camera::getInstance().pp.drawInspector();

        //ImGui::ShowDemoWindow();

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

