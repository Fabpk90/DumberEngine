//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_TRANSFORM_HPP
#define DUMBERENGINE_TRANSFORM_HPP

#include <glm/glm.hpp>
#include<glm/gtc/quaternion.hpp>
#include "GuiComponent.hpp"

class Transform : public GuiComponent
{
private:
    glm::mat4 modelMatrix;
    glm::quat quat;
    glm::vec3 position;
    glm::vec3 scale;

    void updateMatrix();

public:
    Transform();

    void addPosition(glm::vec3 pos);
    void addPosition(float x, float y = 0, float z = 0);
    void setPosition(float x, float y, float z);
    void rotate(glm::vec3 axis, float angle);

    void drawInspector() override;

    glm::mat4& getModelMatrix() { return modelMatrix; };
    glm::vec3& getPosition() { return position; };
};

#endif //DUMBERENGINE_TRANSFORM_HPP
