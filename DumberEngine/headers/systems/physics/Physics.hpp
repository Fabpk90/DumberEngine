//
// Created by fab on 25/04/2020.
//

#ifndef DUMBERENGINE_PHYSICS_HPP
#define DUMBERENGINE_PHYSICS_HPP

#include "bullet/btBulletDynamicsCommon.h"

#include "../ISystem.hpp"
#include "../../components/physics/ICollisionCallbacks.hpp"
#include <map>

class Physics : public ISystem
{
private:
    btDiscreteDynamicsWorld* world;
    std::map<unsigned int*, int> collisions;

    void checkForExitCollisions();

public:

    struct RayCastHit
    {
        glm::vec3 point;
        glm::vec3 normal;
        GameObject* go;
    };

    void init() override;

    void update() override;

    void addRigidBody(btRigidBody* body);
    void removeRigidBody(btRigidBody* body);

    void addCollider(btCollisionObject* shape);
    void removeCollider(btCollisionObject* shape);

    static bool rayCast(glm::vec3 start, glm::vec3 to, RayCastHit& hit);

    static Physics* physicEngine;


};
#endif //DUMBERENGINE_PHYSICS_HPP
