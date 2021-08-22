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
#include "../../../../headers/rendering/renderer/IFbo.hpp"
#include "../../../../headers/rendering/renderer/opengl/GBuffer.hpp"

static void glfwError(int id, const char *description)
{
    std::cout << description << std::endl;
}

static void callbackLoseFocus(GLFWwindow *window, int focus)
{
    bool isFocused = focus == GL_TRUE;

    for(const std::function<void(bool)>& f : IWindow::instance->getCallbacksLoseFocus())
    {
        f(isFocused);
    }
}

void OpenGLRenderer::init(SWindowData data)
{
    instance = this;

    windowSize.x = data.width;
    windowSize.y = data.height;

    std::cout << "Initializing Opengl Renderer" << std::endl;
    glfwSetErrorCallback(&glfwError);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowHandle = glfwCreateWindow(data.width, data.height, data.name.c_str(), nullptr, nullptr);

    if (windowHandle == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
    }
    glfwMakeContextCurrent(windowHandle);
    glfwSetFramebufferSizeCallback(windowHandle, resizeCallback);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    std::cout << "Opengl Renderer initialized" << std::endl;

    glfwSetKeyCallback(windowHandle, InputManager::keyPressed);
    glfwSetCursorPosCallback(windowHandle, InputManager::mouseMoved);
    glfwSetMouseButtonCallback(windowHandle, InputManager::mouseButtonClicked);
    glfwSetWindowFocusCallback(windowHandle, callbackLoseFocus);

    std::cout << "Initializing ImGUI" << std::endl;
    ImGui::CreateContext();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
    ImGui_ImplOpenGL3_Init(nullptr);

    std::cout << "ImGui initialized" << std::endl;

    std::vector<IGBuffer::Param> params = {IGBuffer::Param::Albedo, IGBuffer::Param::Normal};
    gBuffer = std::make_unique<GBuffer>(std::move(params));
}

OpenGLRenderer::~OpenGLRenderer()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(windowHandle);
    glfwTerminate();
    windowHandle = nullptr;

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
    IWindow::instance->setSize(width, height);

    for(ICallbackResize* c : instance->getCallBacksResize())
    {
        c->OnResize(width, height);
    }
}

void OpenGLRenderer::setSize(int width, int height)
{
    windowSize.x = width;
    windowSize.y = height;

    glViewport(0, 0, width, height);
}

void OpenGLRenderer::setVSync(bool isActivated)
{
    if(isActivated)
        glfwSwapInterval(1);
    else
        glfwSwapInterval(0);
}

void OpenGLRenderer::setFramerate(int framerate)
{

}

void OpenGLRenderer::addWindowLoseFocusCallback(std::function<void(bool)> func)
{
    callbacksWindowLoseFocus.push_back(func);
}

std::vector<std::function<void(bool)>> &OpenGLRenderer::getCallbacksLoseFocus()
{
    return callbacksWindowLoseFocus;
}

std::vector<ICallbackResize*> &OpenGLRenderer::getCallBacksResize()
{
    return callbacksWindowResize;
}

void OpenGLRenderer::addWindowResizeCallback(ICallbackResize* callBack)
{
    callbacksWindowResize.push_back(callBack);
}

