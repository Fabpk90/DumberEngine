//
// Created by fab on 23/02/2020.
//

#include "../../../headers/rendering/renderer/IWindow.h"

#include <glad/glad.h>

IWindow* IWindow::instance = nullptr;

GLFWwindow *IWindow::getHandle()
{
    return windowHandle;
}

void IWindow::toggleRenderingType()
{
    glClearColor(0, 0, 0, 0);
    if(renderingType == RenderingType::Forward)
    {
        renderingType = RenderingType::Deferred;

        gBuffer->activate();
        gBuffer->bind();
    }
    else
        renderingType = RenderingType::Forward;
}

void IWindow::setGBuffer(std::unique_ptr<IGBuffer> &&gBuffer)
{
    this->gBuffer = std::move(gBuffer);
}
