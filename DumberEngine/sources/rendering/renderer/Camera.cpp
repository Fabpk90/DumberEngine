//
// Created by fab on 23/02/2020.
//

#include "../../../headers/rendering/renderer/Camera.hpp"
#include "../../../headers/rendering/renderer/IWindow.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera Camera::mainCamera;


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

    updateVecs();
}

void Camera::rotate(glm::vec2 delta)
{
    angles.x += delta.x;
    angles.y -= delta.y;

    if (angles.y > 89.0f)
        angles.y = 89.0f;
    else if (angles.y < -89.0f)
        angles.y = -89.0f;


    direction.x = cos(glm::radians(angles.y)) * cos(glm::radians(angles.x));
    direction.y = sin(glm::radians(angles.y));
    direction.z = cos(glm::radians(angles.y)) * sin(glm::radians(angles.x));

    direction = glm::normalize(direction);

    forward = position + direction * 2.0f;

    updateVecs();
}

Camera &Camera::getInstance()
{
    return mainCamera;
}

Camera::Camera()
{
    angles = glm::vec2();
    forward = glm::vec3(0, 0, -1);
    updateVecs();
}

void Camera::start()
{

}

void Camera::update()
{

}

void Camera::draw()
{

}

void Camera::drawInspector()
{

}

glm::mat4 Camera::getViewMatrix()
{
    return glm::lookAt(position, position + direction, up);
}

glm::mat4 Camera::getProjectionMatrix()
{

    return glm::perspective(glm::radians(60.0f), (float) IWindow::instance->getActualWidth() / (float) IWindow::instance->getActualHeight(), 0.1f, 100.0f);
}

void Camera::moveWorld(glm::vec3& movement)
{
    position += movement;

    updateVecs();
}

