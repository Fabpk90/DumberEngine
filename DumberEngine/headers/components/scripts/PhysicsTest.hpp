//
// Created by fab on 28/08/2020.
//

#ifndef DUMBERENGINE_PHYSICSTEST_HPP
#define DUMBERENGINE_PHYSICSTEST_HPP

#include "../IComponent.hpp"
#include "../physics/ICollisionCallbacks.hpp"

class PhysicsTest : public IComponent, public ICollisionCallbacks
{
public:
    void start() override;

    void update() override;

    void draw() override;

    void drawInspector() override;

    void onCollisionEnter(GameObject *other, glm::vec3 point) override;
};

#endif //DUMBERENGINE_PHYSICSTEST_HPP
