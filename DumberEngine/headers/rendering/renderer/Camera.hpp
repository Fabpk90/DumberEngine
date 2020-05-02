//
// Created by fab on 23/02/2020.
//

#ifndef DUMBERENGINE_CAMERA_HPP
#define DUMBERENGINE_CAMERA_HPP

#include "glm/glm.hpp"
#include "../../components/IComponent.hpp"
#include "IFbo.hpp"
#include "opengl/Vbo.hpp"
#include "../helper/Shader.hpp"
#include "../postprocess/PostProcessStack.hpp"

class Camera : public IComponent
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    glm::vec2 angles;

    PostProcessStack pp;
private:
    static Camera* mainCamera;

    void updateVecs();

public:
    Camera();

    void start() override;

    void update() override;

    void draw() override;

    void drawInspector() override;

    Camera(const Camera &) = delete;

    static Camera &getInstance();

    void move(glm::vec3 movement);
    void moveWorld(glm::vec3 movement);

    void rotate(glm::vec2 delta);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();

    void setPosition(glm::vec3 position);
};

#endif //DUMBERENGINE_CAMERA_HPP
