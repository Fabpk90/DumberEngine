//
// Created by fab on 07/12/2020.
//

#ifndef DUMBERENGINE_POINTLIGHT_HPP
#define DUMBERENGINE_POINTLIGHT_HPP

#include "../IComponent.hpp"
#include "../../rendering/renderer/opengl/Fbo.hpp"
#include "IPostRendering.hpp"
#include <array>

// The optimization to do here is to do some frustum culling.
// The view frustum is tested against each frustum of the light (6).

class PointLight : public IComponent, public IPostRendering
{
private:
    GLuint depthCubeMap;
    glm::mat4 projectionMatrix;
    std::array<glm::mat4, 6> lookAts;
    Fbo* depthMap;

public:
    float range;

public:
    void start() override;

    void update() override;

    void draw() override;

    void postDraw() override;

    ~PointLight() override;

    void drawInspector() override;
};

#endif //DUMBERENGINE_POINTLIGHT_HPP
