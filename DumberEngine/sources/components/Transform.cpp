//
// Created by fab on 25/02/2020.
//

#include <iostream>
#include "../../headers/components/Transform.hpp"

Transform::Transform()
{
    position = glm::vec3(0.f);
    quat = glm::quat();
    modelMatrix = glm::mat4(1.0f);

    scale = glm::vec3(1.0f);
}

void Transform::addPosition(glm::vec3 pos)
{
    position += pos;
}

void Transform::updateMatrix()
{
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, scale);

    //This is done manually for learning purpose
    /*  Rotation matrix =
    *   a^2+b^2-c^2-d^2 & 2bc-2ad & 2ac+2bd \\
       2ad+2bc & a^2-b^2+c^2-d^2 & 2cd-2ab \\
       2bd-2ac & 2ab+2cd & a^2-b^2-c^2+d^2
    */
    //could store all the temp var
    float a2 = quat.x * quat.x;
    float b2 = quat.y * quat.y;
    float c2 = quat.z * quat.z;
    float d2 = quat.w * quat.w;

    glm::mat4 rot = glm::mat4(1.0f);

    rot[0][0] = a2+b2-c2-d2;
    rot[0][1] = (2 * (quat.y * quat.z)) - 2 * (quat.x * quat.w);
    rot[0][2] = 2 * (quat.x * quat.z) + 2 * (quat.y * quat.w);

    rot[1][0] = 2 * (quat.x * quat.w) + 2 * (quat.y * quat.z);
    rot[1][1] = a2-b2+c2-d2;
    rot[1][2] = 2 * (quat.z * quat.w) - 2 * (quat.x * quat.y);

    rot[2][0] = 2 * (quat.y * quat.w) - 2 * (quat.x * quat.z);
    rot[2][1] = 2 * (quat.x * quat.y) + 2 * (quat.z * quat.w);
    rot[2][2] = a2-b2-c2+d2;

    modelMatrix = rot * modelMatrix;
}

void Transform::rotate(glm::vec3 axis, float angle)
{
    axis = glm::normalize(axis);
    axis = glm::sin(glm::radians(angle/2)) * axis;

    glm::quat q;
    q.x = glm::cos(glm::radians(angle / 2)); //a
    q.y = axis.x; // b
    q.z = axis.y; // c
    q.w = axis.z; // d

    quat *= q;

    updateMatrix();
}

void Transform::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;

    modelMatrix[3] = glm::vec4(position, 1.0f);
}

void Transform::addPosition(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;

    modelMatrix[3] = glm::vec4(position, 1.0f);
}
