//
// Created by fab on 25/04/2020.
//

#ifndef DUMBERENGINE_PHYSICS_HPP
#define DUMBERENGINE_PHYSICS_HPP

#include "bullet/btBulletDynamicsCommon.h"

#include "../ISystem.hpp"

class Physics : public ISystem
{
private:
    btDiscreteDynamicsWorld* world;

public:
    void init() override;

    void update() override;

    void addRigidBody(btRigidBody* body);
    void removeRigidBody(btRigidBody* body);

    void addCollider(btCollisionObject* shape);
    void removeCollider(btCollisionObject* shape);

    static Physics* physicEngine;
};
#endif //DUMBERENGINE_PHYSICS_HPP
