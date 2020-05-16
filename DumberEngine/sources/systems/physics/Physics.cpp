//
// Created by fab on 25/04/2020.
//

#include <iostream>
#include "../../../headers/systems/physics/Physics.hpp"
#include "../../../headers/rendering/helper/Time.hpp"

Physics* Physics::physicEngine = nullptr;

void Physics::init()
{
    physicEngine = this;

    ///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
    btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();

    ///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
    btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

    ///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
    btBroadphaseInterface* overlappingPairCache = new btDbvtBroadphase();

    ///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
    btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

    world = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);

    world->setGravity(btVector3(0, -9.81f, 0));
}

void Physics::update()
{
    //todo: be frame independent maybe
    world->stepSimulation(Time::getInstance().deltaTime);
}

void Physics::addRigidBody(btRigidBody *body)
{
    world->addRigidBody(body);
}

void Physics::removeRigidBody(btRigidBody* body)
{
    world->removeRigidBody(body);
}

void Physics::addCollider(btCollisionObject *shape)
{
    world->addCollisionObject(shape);
}

void Physics::removeCollider(btCollisionObject *shape)
{
    world->removeCollisionObject(shape);
}
