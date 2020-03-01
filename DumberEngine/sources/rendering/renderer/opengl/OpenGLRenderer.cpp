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

static void glfwError(int id, const char *description)
{
    std::cout << description << std::endl;
}

void OpenGLRenderer::init(SWindowData data)
{
    instance = this;
    windowSize.x = data.width;
    windowSize.y = data.height;

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
    glfwSetFramebufferSizeCallback(windowHandle, resizeCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        release();
    }

    std::cout << "Opengl Renderer initialized" << std::endl;

    std::cout << "Initializing the Input Manager" << std::endl;
    InputManager::getInstance().renderer = this;

    glfwSetKeyCallback(windowHandle, InputManager::keyPressed);
    glfwSetCursorPosCallback(windowHandle, InputManager::mouseMoved);
    glfwSetMouseButtonCallback(windowHandle, InputManager::mouseButtonClicked);

    std::cout << "Input Manager initialized" << std::endl;

    std::cout << "Initializing ImGUI" << std::endl;
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
    ImGui_ImplOpenGL3_Init(NULL);

    std::cout << "ImGui initialized" << std::endl;
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

void OpenGLRenderer::closeWindow()
{
    glfwSetWindowShouldClose(windowHandle, true);
}

int OpenGLRenderer::getActualWidth()
{
    return windowSize.x;
}

int OpenGLRenderer::getActualHeight()
{
    return windowSize.y;
}

void OpenGLRenderer::resizeCallback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);

    IWindow::instance->setSize(width, height);
}

void OpenGLRenderer::setSize(int width, int height)
{
    windowSize.x = width;
    windowSize.y = height;
}

