//
// Created by fab on 02/05/2020.
//

#include "../../../headers/systems/rendering/ShadowMapping.hpp"
#include "../../../headers/components/scripts/World.hpp"

ShadowMapping* ShadowMapping::shadowMapping = nullptr;

ShadowMapping::ShadowMapping(uint32_t width, uint32_t height) : shadowShader("shaders/forward/shadow/")
, width(width), height(height)
{
    fbo = new Fbo(width, height, true);
    fbo->bind();
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    fbo->unBind();
}

void ShadowMapping::draw()
{
    fbo->bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_BLEND);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    shadowShader.use();
    shadowShader.setMatrix4("lightSpaceMatrix", projectionMatrix);

    Scene::instance->drawCastingShadowObjects(&shadowShader);
}

ShadowMapping::~ShadowMapping()
{
    delete fbo;
}

