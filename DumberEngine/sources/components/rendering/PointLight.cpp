//
// Created by fab on 07/12/2020.
//

#include <imgui/imgui.h>
#include "../../../headers/components/IComponent.hpp"
#include "../../../headers/components/rendering/PointLight.hpp"
#include "../../../headers/rendering/Scene.hpp"

constexpr unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;

void PointLight::start()
{
    IComponent::start();

    shader = new Shader("shaders/forward/pointlightShadow/");

    glGenTextures(1, &depthCubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);

    for (int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
                     nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    depthMap = new Fbo(SHADOW_WIDTH, SHADOW_HEIGHT, -1, depthCubeMap);
    depthMap->enableRead(false);
    depthMap->enableWrite(false);

    projectionMatrix = glm::perspective(glm::radians(60.0f)
            ,(float) IWindow::instance->getActualWidth() / (float) IWindow::instance->getActualHeight()
    , 0.1f, 100.0f);

    lookAts[0] = projectionMatrix * glm::lookAt(transform->getPosition(), transform->getPosition() + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    lookAts[1] = projectionMatrix * glm::lookAt(transform->getPosition(), transform->getPosition() + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));
    lookAts[2] = projectionMatrix * glm::lookAt(transform->getPosition(), transform->getPosition() + glm::vec3(.0f, 1.0f, 0.0f), glm::vec3(0.0f, .0f, 1.0f));
    lookAts[2] = projectionMatrix * glm::lookAt(transform->getPosition(), transform->getPosition() + glm::vec3(.0f, -1.0f, 0.0f), glm::vec3(0.0f, .0f, -1.0f));
    lookAts[2] = projectionMatrix * glm::lookAt(transform->getPosition(), transform->getPosition() + glm::vec3(.0f, .0f, 1.0f), glm::vec3(0.0f, -1.0f, .0f));
    lookAts[2] = projectionMatrix * glm::lookAt(transform->getPosition(), transform->getPosition() + glm::vec3(.0f, .0f, -1.0f), glm::vec3(0.0f, -1.0f, .0f));
}

void PointLight::update()
{
    IComponent::update();
}

void PointLight::draw()
{
    IComponent::draw();
}

PointLight::~PointLight()
{
    delete depthMap;
    delete shader;
}

void PointLight::drawInspector()
{
    IComponent::drawInspector();

    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
    ImGui::Image((void*)(intptr_t) depthCubeMap, ImVec2(SHADOW_WIDTH, SHADOW_HEIGHT));
}

void PointLight::postDraw()
{
    int previousHeight = IWindow::instance->getActualHeight();
    int previousWidth = IWindow::instance->getActualHeight();

    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubeMap);
    glClear(GL_DEPTH_BUFFER_BIT);

    Scene::instance->drawCastingShadowObjects(shader);


    glViewport(0, 0, previousWidth, previousHeight);
}
