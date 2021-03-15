//
// Created by fab on 23/02/2020.
//

#include "../../../headers/rendering/renderer/IWindow.h"

IWindow* IWindow::instance = nullptr;

GLFWwindow *IWindow::getHandle()
{
    return windowHandle;
}

void IWindow::toggleRenderingType()
{
    if(renderingType == RenderingType::Forward)
    {
        renderingType = RenderingType::Deferred;
        gBuffer->activate();
    }
    else
        renderingType = RenderingType::Forward;
}

void IWindow::setGBuffer(std::unique_ptr<IGBuffer> &&gBuffer)
{
    this->gBuffer = std::move(gBuffer);
}
