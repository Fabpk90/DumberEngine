//
// Created by fab on 28/04/2020.
//

#ifndef DUMBERENGINE_AVATAR_HPP
#define DUMBERENGINE_AVATAR_HPP

#include "../IComponent.hpp"
#include "../../rendering/renderer/Camera.hpp"
#include "World.hpp"

class Avatar : public IComponent
{
private:
    Camera* cam;
    World* world;

    glm::vec3 position;

    bool move;
    bool jump;
    float height;
    float currentHeight;
    float width;
    bool forward;
    bool backward;
    bool left;
    bool right;
    bool standing;
    bool inWater;
    bool crouch;
    bool run;

    glm::vec3 gravity;
    glm::vec3 damping;
    float mass;

    float maxSpeed = 70;

    glm::vec3 startPositionRayCast;
    glm::vec3 endPositionRayCast;

    const float maxRaycastDistance = 2.5f;
public:
    void drawInspector() override;

    void start() override;

    void update() override;

    void draw() override;

    void rayCast();

    void setWorld(World* world) {  this->world = world; }


    void setCamera(Camera *pCamera);
};
#endif //DUMBERENGINE_AVATAR_HPP
