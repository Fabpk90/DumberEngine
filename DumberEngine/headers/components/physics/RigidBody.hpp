//
// Created by fab on 11/05/2020.
//

#ifndef DUMBERENGINE_RIGIDBODY_HPP
#define DUMBERENGINE_RIGIDBODY_HPP

#include <bullet/btBulletDynamicsCommon.h>
#include "../IComponent.hpp"
#include "../../systems/physics/Physics.hpp"
#include "ICollisionCallbacks.hpp"

class RigidBody : public IComponent, public ICollisionCallbacks
{
private:
    float mass;
    btVector3 localInertia;
    btTransform physicsTransform;

    btCollisionShape* shape;
    btRigidBody* body;
    btDefaultMotionState* motionState;
    bool isDynamic;
public:
    void drawInspector() override;

    void start() override;

    void update() override;

    void draw() override;

    virtual void onCollisionEnter(ICollisionCallbacks *other, glm::vec3 point) override;

    virtual void onCollisionStay(ICollisionCallbacks *other, glm::vec3 point) override;

    virtual void onCollisionExit() override;

    ~RigidBody()
    {
        Physics::physicEngine->removeRigidBody(body);

        delete shape;
        delete body;
    }
};
#endif //DUMBERENGINE_RIGIDBODY_HPP
