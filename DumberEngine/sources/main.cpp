//
// Created by fab on 22/02/2020.
//

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "glad/glad.h"
#include "glad/glad.c"
#include "glfw/glfw3.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include <string>
#include <iostream>

#include "../headers/rendering/renderer/opengl/OpenGLRenderer.hpp"
#include "../headers/rendering/helper/Shader.hpp"
#include "../headers/rendering/renderer/opengl/Vbo.hpp"
#include "../headers/rendering/renderer/Camera.hpp"
#include "../headers/rendering/helper/Time.hpp"
#include "../headers/rendering/renderer/opengl/InputManager.hpp"


Vbo* createCube()
{
    auto vbo = new Vbo(3, 36);

    // Définition du contenu VBO
    vbo->setElementDescription(0, Vbo::Element(3)); //Sommet
    vbo->setElementDescription(1, Vbo::Element(3)); //Normal
    vbo->setElementDescription(2, Vbo::Element(2)); //UV

    vbo->createCPUSide();

    // On ajoute les sommets
    int iVertice = 0;

    // Surface 1
    vbo->setElementData(0, iVertice, 0, 0, 0);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 1
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;

    // Surface 2
    vbo->setElementData(0, iVertice, 0, 0, 0);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 2
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;


    // Surface 3
    vbo->setElementData(0, iVertice, 0, 0, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 3
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;


    // Surface 1
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 1
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 1);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;


    // Surface 2
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 2
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 1);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;


    // Surface 3
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 3
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);

    vbo->createGPUSide();
    // On envoie le contenu au GPU
    vbo->deleteCPUSide();

    return vbo;
}

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
            default:                               error = "AY CARAMBA"; break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

OpenGLRenderer renderer = OpenGLRenderer();

void updateCamera(Camera& cam)
{
    auto& input = InputManager::getInstance();

    glm::vec3 movement = glm::vec3();

    if(input.isKeyPressed(GLFW_KEY_W))
    {
        movement.z += 2;
    }
    else if(input.isKeyPressed(GLFW_KEY_S))
    {
        movement.z -= 2;
    }
    if(input.isKeyPressed(GLFW_KEY_A))
    {
        movement.x -= 2;
    }
    else if(input.isKeyPressed(GLFW_KEY_D))
    {
        movement.x += 2;
    }

    if(input.isKeyPressed(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(renderer.GetHandle(), true);
    }

    movement *= Time::getInstance().deltaTime;

    cam.move(movement);
}

int main(int argc, char** argv)
{

    SWindowData data {};
    data.width = 800;
    data.height = 600;
    data.name = "Dumber Engine";

    renderer.init(data);

    auto handle = renderer.GetHandle();

    Camera cam = Camera(glm::vec3(0, -5, 0));

    Shader* shader = new Shader("shaders/cube/");
    glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)data.width / (float)data.height, 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(-0.25f, 0, 0));

    Vbo* vbo = createCube();

    bool show_demo_window = true;
    float lastFrame = 0;
    while(!glfwWindowShouldClose(handle))
    {
        float currentFrame = glfwGetTime();
        Time::getInstance().deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        updateCamera(cam);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        shader->setMatrix4("model", model);

        glm::mat4 view = glm::lookAt(cam.position, cam.position + cam.direction, cam.up);
        shader->setMatrix4("view", view);
        shader->setMatrix4("projection", proj);
        vbo->draw();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(handle);
        glfwPollEvents();
    }

    return 0;
}


