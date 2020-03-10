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

#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>



void Engine::start()
{
    SWindowData data{};
    data.width = 800;
    data.height = 600;
    data.name = "Dumber Engine";

    window = new OpenGLRenderer();
    window->init(data);

    InputManager* inputManager = new InputManager();

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

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene->update();
        scene->draw();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        scene->drawInspector();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window->getHandle());
        glfwPollEvents();
    }
}

