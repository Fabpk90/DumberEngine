//
// Created by fab on 31/08/2020.
//

#include "../../headers/debug/DebugDraw.hpp"

DebugDraw* DebugDraw::instance = nullptr;

void DebugDraw::DrawLine(glm::vec3 from, glm::vec3 to, glm::vec3 color)
{
    if(shaderDebug == nullptr)
    {
        shaderDebug = new Shader("shaders/debug/");
    }

    if(vbo == nullptr)
    {
        vbo = new Vbo(1, 2);
        vbo->setElementDescription(0, Vbo::Element(3));

        vbo->createCPUSide();
    }

    glm::mat4 v = Camera::getInstance().getViewMatrix();
    shaderDebug->setMatrix4("v", v);
    auto p = Camera::getInstance().getProjectionMatrix();
    shaderDebug->setMatrix4("p", p);

    shaderDebug->setVec3("color", color);

    vbo->deleteGPUSide();

    vbo->setElementData(0, 0, from.x+ 0.25f, from.y, from.z);
    vbo->setElementData(0, 1, to.x, to.y, to.z);

    vbo->createGPUSide();
    vbo->bind();

    glLineWidth(3.3f);
    glDrawArrays(GL_LINES, 0, 2);
    glLineWidth(1.0f);

}
