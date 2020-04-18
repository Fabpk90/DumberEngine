//
// Created by fab on 09/04/2020.
//

#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "../../../headers/rendering/postprocess/PostProcessStack.hpp"
#include "../../../headers/rendering/renderer/IWindow.h"

void PostProcessStack::addPostProcess(IPostProcess *pp)
{
    stack.push_front(pp);
}

void PostProcessStack::drawInspector()
{
    for(IPostProcess* pp : stack)
    {
        ImGui::Text("%s", pp->getName().c_str());
        ImGui::Checkbox("Activated ?", pp->getIsActive());

        //TODO: change this, make it all into the pp (virtual in IPostProcess)
        pp->drawInspector();
    }
}

void PostProcessStack::draw()
{
    shaderQuad.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo->getColorTexture());

    shaderQuad.setInt("TexColor", 0);

    vboQuad->draw();
}

PostProcessStack::PostProcessStack() : shaderQuad("shaders/quad/")
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

    SUniforms uni;

    uni.screen_height = IWindow::instance->getActualHeight();
    uni.screen_width = IWindow::instance->getActualWidth();

    uni.near_far = glm::vec2(0.1f, 100.0f);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(SUniforms), &uni, GL_STREAM_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(SUniforms) - sizeof(glm::vec2), sizeof(glm::vec2), glm::value_ptr(uni.near_far));

    fbo = new Fbo(uni.screen_width, uni.screen_height, true, true);
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

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo->getColorTexture());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, fbo->getDepthTexture());

    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo);

    for(IPostProcess* pp : stack)
    {
        if(*pp->getIsActive())
            pp->renderEffect(vboQuad);
    }

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

