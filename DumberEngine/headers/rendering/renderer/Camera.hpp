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

class Camera : public IComponent
{
public:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    glm::vec2 angles;
private:
    static Camera* mainCamera;

    void updateVecs();



    IFbo* fbo;
    Vbo* vboQuad;
    Shader shaderPostProcessing;
    Shader shaderQuad;

public:
    Camera();

    void start() override;

    void update() override;

    void draw() override;

    void drawInspector() override;

    void drawScene();

    Camera(const Camera &) = delete;

    static Camera &getInstance();

    void move(glm::vec3 movement);
    void moveWorld(glm::vec3 movement);

    IFbo& getFbo() { return *fbo; }
    void activatePostProcessing();

    void rotate(glm::vec2 delta);

    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix();
};

#endif //DUMBERENGINE_CAMERA_HPP
