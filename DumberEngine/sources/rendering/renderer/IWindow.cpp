//
// Created by fab on 23/02/2020.
//

#include "../../../headers/rendering/renderer/IWindow.h"

#include <imgui/imgui.h>
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
    {
        renderingType = RenderingType::Forward;
        gBuffer->deActivate();
    }
}

void IWindow::setGBuffer(std::unique_ptr<IGBuffer> &&gBuffer)
{
    this->gBuffer = std::move(gBuffer);
}

void IWindow::drawGUITools()
{
    ImGui::Begin("Tools");

    auto& gBuffer = IWindow::instance->getGBuffer();

    if(gBuffer->getIsActive())
    {
        auto& gBuffer = IWindow::instance->getGBuffer();
        for (auto& desc : gBuffer->getDescriptors())
        {
            auto id = gBuffer->getID(desc);

            ImGui::Image((void*)(intptr_t) id, ImVec2(512, 512));
        }

    }

    ImGui::End();
}
