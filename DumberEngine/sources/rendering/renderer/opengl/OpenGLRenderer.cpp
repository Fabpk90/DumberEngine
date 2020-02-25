//
// Created by fab on 23/02/2020.
//
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

#include <iostream>
#include <glad/glad.h>
#include "../../../../headers/rendering/renderer/opengl/OpenGLRenderer.hpp"
#include "../../../../headers/rendering/renderer/opengl/InputManager.hpp"

static void glfwError(int id, const char* description)
{
    std::cout << description << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void OpenGLRenderer::init(SWindowData data)
{
    std::cout << "Initializing Opengl Renderer" << std::endl;
    glfwSetErrorCallback(&glfwError);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    windowHandle = glfwCreateWindow(data.width, data.height, data.name, NULL, NULL);


    if (windowHandle == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        release();
    }
    glfwMakeContextCurrent(windowHandle);
    glfwSetFramebufferSizeCallback(windowHandle, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        release();
    }

    std::cout << "Opengl Renderer initialized" << std::endl;

    glfwSetKeyCallback(windowHandle, InputManager::keyPressed);
    glfwSetCursorPosCallback(windowHandle, InputManager::mouseMoved);

  ImGui::CreateContext();


  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  //ImGui::StyleColorsClassic();

  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
  ImGui_ImplOpenGL3_Init(NULL);
}

void OpenGLRenderer::release()
{
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(windowHandle);
  glfwTerminate();
  windowHandle = nullptr;
}

OpenGLRenderer::~OpenGLRenderer()
{
    release();

    std::cout << "Destroying the OpenGL Renderer" << std::endl;
}

