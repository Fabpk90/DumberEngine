//
// Created by fab on 10/05/2020.
//

#ifndef DUMBERENGINE_BOXCOLLIDER_HPP
#define DUMBERENGINE_BOXCOLLIDER_HPP

#include <bullet/btBulletDynamicsCommon.h>
#include "../IComponent.hpp"
#include "../../systems/physics/Physics.hpp"
#include "../../debug/CubeDebug.hpp"
#include "ICollisionCallbacks.hpp"

class BoxCollider : public IComponent
{
private:

    float mass;
    btRigidBody* body;

    CubeDebug* cube;

    bool isStatic;

public:

    BoxCollider()
    {
        //TODO: maybe the addcollisionshape adds a static object, maybe but needs some digging !
        shape = new btBoxShape(btVector3(btScalar(1.0f), btScalar(1.0f), btScalar(1.0f)));
    }

    void drawInspector() override;

    void start() override;

    void update() override;

    void draw() override;

    void setColliderScale(btVector3 scale);

public:

    ~BoxCollider()
    {
        if(isStatic)
        {
            Physics::physicEngine->removeRigidBody(body);

            //delete physicsTransform;
            //delete body;
        }

        delete cube;
    }

    btBoxShape* shape;
    btTransform* physicsTransform;
};
#endif //DUMBERENGINE_BOXCOLLIDER_HPP
