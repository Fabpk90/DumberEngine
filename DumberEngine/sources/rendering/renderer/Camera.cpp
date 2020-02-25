//
// Created by fab on 23/02/2020.
//

#include "../../../headers/rendering/renderer/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) : position(position)
{
    forward = glm::vec3(0, 0, -1);
    updateVecs();
}

void Camera::updateVecs()
{
    direction = glm::normalize(forward - position);
    right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
    up = glm::normalize(glm::cross(right, direction));
}

void Camera::move(glm::vec3& m)
{
    position += direction * m.z;
    position += right * m.x;
    position += up * m.y;

    forward = position + direction * 2.0f;

    //updateVecs();
}

void Camera::rotate(glm::vec2 angle)
{
    direction.x = cos(glm::radians(angle.x)) * cos(glm::radians(angle.y));
    direction.y = sin(glm::radians(angle.y));
    direction.z = sin(glm::radians(angle.x)) * cos(glm::radians(angle.y));

    direction = glm::normalize(direction);

    updateVecs();
}

