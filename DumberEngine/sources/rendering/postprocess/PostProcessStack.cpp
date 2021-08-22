//
// Created by fab on 09/04/2020.
//

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <algorithm>
#include "../../../headers/rendering/postprocess/PostProcessStack.hpp"
#include "../../../headers/rendering/renderer/opengl/GBuffer.hpp"

void PostProcessStack::addPostProcess(IPostProcess *pp)
{
    stack.push_front(pp);
}

void PostProcessStack::drawInspector()
{
    ImGui::Begin("Post Process");
    for(IPostProcess* pp : stack)
    {
        pp->drawInspector();
    }
    ImGui::End();
}

void PostProcessStack::draw()
{
    shaderQuad.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo0->getColorTexture());

    shaderQuad.setInt("TexColor", 0);

    vboQuad->draw();
}

PostProcessStack::PostProcessStack() : shaderQuad("shaders/forward/quad/")
{
    vboQuad = new Vbo(1, 6);
    vboQuad->setElementDescription(0, Vbo::Element(3));
    vboQuad->createCPUSide();

    vboQuad->setElementData(0, 0, -1, -1, 0);
    vboQuad->setElementData(0, 1, 1, -1, 0);
    vboQuad->setElementData(0, 2, -1, 1, 0);
    vboQuad->setElementData(0, 3, -1, 1, 0);
    vboQuad->setElementData(0, 4, 1, -1, 0);
    vboQuad->setElementData(0, 5, 1, 1, 0);

    vboQuad->createGPUSide();
    vboQuad->deleteCPUSide();

    glGenBuffers(1, &ubo);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);

    SUniforms uni{};

    uni.screen_height = IWindow::instance->getActualHeight();
    uni.screen_width = IWindow::instance->getActualWidth();

    uni.near_far = glm::vec2(0.1f, 100.0f);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(SUniforms), &uni, GL_STREAM_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(SUniforms) - sizeof(glm::vec2), sizeof(glm::vec2), glm::value_ptr(uni.near_far));

    fbo0 = new Fbo(uni.screen_width, uni.screen_height, true, false, true);
    glGenTextures(1, &texFBO0);
    glGenTextures(1, &texFBO1);

    glBindTexture(GL_TEXTURE_2D, texFBO0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, uni.screen_width,  uni.screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glBindTexture(GL_TEXTURE_2D, texFBO1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, uni.screen_width,  uni.screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    fbo0->setColorTexture(texFBO0);

    IWindow::instance->addWindowResizeCallback(this);
}

PostProcessStack::~PostProcessStack()
{
    delete vboQuad;

    for(IPostProcess* pp : stack)
    {
        delete pp;
    }
}

void PostProcessStack::activateEffects()
{
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbo0->getDepthTexture());

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

    if(!IWindow::instance->isForward())
    {
        glBindFramebuffer(GL_READ_BUFFER, fbo0->getID());
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dynamic_cast<GBuffer*>(IWindow::instance->getGBuffer().get())->getIDFbo());
        glBlitFramebuffer(0, 0, 1280, 720, 0, 0, 1280, 720, GL_COLOR_BUFFER_BIT, GL_LINEAR);
    }


    glActiveTexture(GL_TEXTURE0);
    for(IPostProcess* pp : stack)
    {
        if(pp->getIsActive())
        {
            if(isFirstFboBound)
            {
                fbo0->setColorTexture(texFBO1);

                glBindTexture(GL_TEXTURE_2D, texFBO0);

                isFirstFboBound = false;
            }
            else
            {
                fbo0->setColorTexture(texFBO0);

                glBindTexture(GL_TEXTURE_2D, texFBO1);

                isFirstFboBound = true;
            }

            pp->renderEffect(vboQuad);
        }
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void PostProcessStack::OnResize(int width, int height)
{
    glBindBuffer(GL_UNIFORM_BUFFER, ubo);
    SUniforms uni{};

    uni.screen_height = IWindow::instance->getActualHeight();
    uni.screen_width = IWindow::instance->getActualWidth();

    uni.near_far = glm::vec2(0.1f, 100.0f);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(SUniforms), &uni, GL_STREAM_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(SUniforms) - sizeof(glm::vec2), sizeof(glm::vec2), glm::value_ptr(uni.near_far));
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

    glBindTexture(GL_TEXTURE_2D, texFBO0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, uni.screen_width,  uni.screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glBindTexture(GL_TEXTURE_2D, texFBO1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, uni.screen_width,  uni.screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
}

int PostProcessStack::getActiveEffects()
{
    return
    std::count_if(stack.begin(), stack.end(), [](IPostProcess* elm) { return elm->getIsActive();});
}

