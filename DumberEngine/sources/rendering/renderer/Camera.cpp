//
// Created by fab on 23/02/2020.
//

#include "../../../headers/rendering/renderer/Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position) : position(position)
{
    angles = glm::vec2();
    forward = glm::vec3(0, 0, -1);
    updateVecs();
}

void Camera::updateVecs()
{
    direction = glm::normalize(forward - position);
    right = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
    up = glm::normalize(glm::cross(right, direction));
}

void Camera::move(glm::vec3 &m)
{
    position += direction * m.z;
    position += right * m.x;
    position += up * m.y;

    forward = position + direction * 2.0f;
}

void Camera::rotate(glm::vec2 delta)
{
    angles += delta;

    if (angles.y > 89.0f)
        angles.y = 89.0f;
    else if (angles.y < -89.0f)
        angles.y = -89.0f;

    float x = angles.x * 0.2f;
    float y = angles.y * 0.2f;

    direction.x = cos(glm::radians(x)) * cos(glm::radians(y));
    direction.y = sin(glm::radians(y));
    direction.z = sin(glm::radians(x)) * cos(glm::radians(y));

    direction = glm::normalize(direction);

    forward = position + direction * 2.0f;

    updateVecs();
}

