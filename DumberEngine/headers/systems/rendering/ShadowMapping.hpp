//
// Created by fab on 02/05/2020.
//

#ifndef DUMBERENGINE_SHADOWMAPPING_HPP
#define DUMBERENGINE_SHADOWMAPPING_HPP

#include "../../rendering/renderer/opengl/Fbo.hpp"
#include "../ISystem.hpp"
#include "../../rendering/helper/Shader.hpp"
#include "../../rendering/Scene.hpp"
#include "../../components/scripts/World.hpp"

class ShadowMapping
{
public:
    void draw();

    ~ShadowMapping();

    ShadowMapping(uint32_t width, uint32_t height);
    IFbo& getFbo() { return *fbo;}

    static ShadowMapping* getInstance()
    {
        if(shadowMapping == nullptr)
        {
            shadowMapping = new ShadowMapping(4096, 4096);
        }
        return shadowMapping;
    }

    glm::mat4& getProjectionMatrix()
    {
        glm::mat4 lightProjection = glm::ortho(-64.0f, 64.0f, -64.0f, 64.0f, 1.f, 100.0f);
        glm::mat4 lightLookAt =  glm::lookAt((World::sunDirection),
                                             glm::vec3( 0.0f, 0.0f,  0.0f),
                                             glm::vec3( 0.0f, 1.0f,  0.0f));
        projectionMatrix = lightProjection * lightLookAt;
        return projectionMatrix;
    }

private:
    Fbo* fbo;
    glm::mat4 projectionMatrix;
    Shader shadowShader;

    uint32_t width;
    uint32_t height;

public:
    static ShadowMapping* shadowMapping;
};
#endif //DUMBERENGINE_SHADOWMAPPING_HPP
