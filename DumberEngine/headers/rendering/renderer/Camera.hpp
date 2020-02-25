//
// Created by fab on 23/02/2020.
//

#ifndef DUMBERENGINE_CAMERA_HPP
#define DUMBERENGINE_CAMERA_HPP

#include "glm/glm.hpp"

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    glm::vec2 angles;

private:
    void updateVecs();

public:
    Camera(glm::vec3 position);

    void move(glm::vec3 &movement);

    void rotate(glm::vec2 delta);
};

#endif //DUMBERENGINE_CAMERA_HPP
