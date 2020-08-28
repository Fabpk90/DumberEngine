//
// Created by fab on 25/04/2020.
//

#include <iostream>
#include "../../../headers/systems/physics/Physics.hpp"
#include "../../../headers/rendering/helper/Time.hpp"
#include "../../../headers/components/physics/BoxCollider.hpp"

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

    int numManifolds = world->getDispatcher()->getNumManifolds();
    for (int i=0; i<numManifolds; i++)
    {
        //2
        btPersistentManifold* contactManifold = world->getDispatcher()->getManifoldByIndexInternal(i);

        //3
        int numContacts = contactManifold->getNumContacts();
        if (numContacts > 0)
        {
            const btCollisionObject* obA = contactManifold->getBody0();
            const btCollisionObject* obB = contactManifold->getBody1();

            auto col0 = (ICollisionCallbacks*) obA->getUserPointer();
            auto col1 = (ICollisionCallbacks*) obB->getUserPointer();

            if(col0)
            {
                auto pointBullet = contactManifold->getContactPoint(0).getPositionWorldOnA();
                glm::vec3 point(pointBullet[0], pointBullet[1], pointBullet[2]);

                auto found = collisions.find(col0);

                if(found == collisions.end())
                {
                    collisions[col0] = 1;
                    col0->onCollisionEnter(col1, point);
                }
                else
                {
                    collisions[col0] = 1;
                    col0->onCollisionStay(col1, point);
                }
            }

            if(col1)
            {
                auto pointBullet = contactManifold->getContactPoint(0).getPositionWorldOnB();
                glm::vec3 point(pointBullet[0], pointBullet[1], pointBullet[2]);

                auto found = collisions.find(col1);

                if(found == collisions.end())
                {
                    collisions[col1] = 1;
                    col1->onCollisionEnter(col0, point);
                }
                else
                {
                    collisions[col1] = 1;
                    col1->onCollisionStay(col0, point);
                }
            }

        }
    }

    checkForExitCollisions();
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

void Physics::checkForExitCollisions()
{
    auto iterator = collisions.begin();

    while (iterator != collisions.end())
    {
        if(--(*iterator).second < 0)
        {
            (*iterator).first->onCollisionExit();
           iterator = collisions.erase(iterator);
        }
        else
            iterator++;
    }
}
