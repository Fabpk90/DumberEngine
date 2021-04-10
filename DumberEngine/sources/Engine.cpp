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
#include "../headers/systems/rendering/ShadowMapping.hpp"
#include "../headers/systems/physics/Physics.hpp"
#include "../headers/components/physics/BoxCollider.hpp"
#include "../headers/components/physics/RigidBody.hpp"
#include "../headers/components/scripts/PhysicsTest.hpp"
#include "../headers/components/rendering/StaticMesh.hpp"
#include "../headers/systems/Editor.hpp"
#include "../headers/components/rendering/PointLight.hpp"

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

    auto o = Scene::instance->createGameObject("Camera");
    o->addComponent<Camera>();
    o->addComponent<CameraScript>();


    auto worldGO = Scene::instance->createGameObject("World");
    worldGO->addComponent<World>();

    auto avatarGO = Scene::instance->createGameObject("Avatar");

    //Avatar* avatar = new Avatar();
    //avatar->setWorld(world);
   // avatar->setCamera(cam);

    avatarGO->addComponent(new CameraScript());

    auto phy = Scene::instance->createGameObject("RigidBody");
    phy->addComponent(new BoxCollider());
    phy->addComponent(new RigidBody());

    auto test = phy->addComponent<PhysicsTest>();
    test->test = "yeppa";

    auto box = Scene::instance->createGameObject("BoxCollider");
    box->addComponent(new BoxCollider());

    auto test1 = box->addComponent<PhysicsTest>();
    test1->test = "nooope";

    auto meshGO = Scene::instance->createGameObject("StaticMesh");
    auto sm = meshGO->addComponent<StaticMesh>();
    sm->loadFrom("mesh/Cerberus/Cerberus_LP.fbx");

    auto pointLightGO = Scene::instance->createGameObject("PointLight");
    pointLightGO->addComponent(new PointLight());


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
        else if(IInputManager::instance->isKeyPressed(GLFW_KEY_F1))
        {
            IWindow::instance->toggleRenderingType();
        }

        scene->update();

        //shadow pass
        ShadowMapping::getInstance()->draw();

        //post process
        if(IWindow::instance->isForward())
            Camera::getInstance().pp.getFBO().bind();
        else
            IWindow::instance->getGBuffer()->bind();

        glViewport(0, 0, IWindow::instance->getActualWidth(), IWindow::instance->getActualHeight());

        glClearColor(window->getClearColor().x, window->getClearColor().y, window->getClearColor().z, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCullFace(GL_BACK);

        scene->draw();

        //Quick fix, need to handle forward -> deferred changing
        // as the pp uses the same fbo
        if(IWindow::instance->isForward())
            scene->drawPostRendering();
        else
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);

            glClearColor(window->getClearColor().x, window->getClearColor().y, window->getClearColor().z, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        }
        //debug->draw();


      //  glCullFace(GL_BACK);

        //GUI
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::ShowMetricsWindow();

        scene->drawInspector();

        Camera::getInstance().pp.drawInspector();

        ImGui::ShowDemoWindow();

        IWindow::drawGUITools();

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
    delete scene;
    delete window;

    for(ISystem* s : systems)
    {
        delete s;
    }
}

