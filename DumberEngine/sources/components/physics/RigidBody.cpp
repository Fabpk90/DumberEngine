//
// Created by fab on 11/05/2020.
//

#include <imgui/imgui.h>
#include "../../../headers/components/physics/RigidBody.hpp"
#include "../../../headers/rendering/Scene.hpp"
#include "../../../headers/components/physics/BoxCollider.hpp"

void RigidBody::drawInspector()
{
    physicsTransform = body->getWorldTransform();

    ImGui::Text("Position %f %f %f", float(physicsTransform.getOrigin().x()), physicsTransform.getOrigin().y(), physicsTransform.getOrigin().z());
}

void RigidBody::start()
{
    auto* collider = Scene::getGameObject(*gameObjectIndex)->getComponent<BoxCollider>();
    collider->setColliderScale(btVector3(15, 15, 15));

    shape = collider->shape;
    collider->physicsTransform = &physicsTransform;

    physicsTransform.setIdentity();
    physicsTransform.setOrigin(btVector3(0.0f, 50.0f, 0.0f));

    //rigidbody is dynamic if and only if mass is non zero, otherwise static
    mass = btScalar(1.0f);
    isDynamic = mass != 0.0f;

    shape->calculateLocalInertia(mass, localInertia);

    motionState = new btDefaultMotionState(physicsTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, motionState, shape, localInertia);

    body = new btRigidBody(rbInfo);

    Physics::physicEngine->addRigidBody(body);
}

void RigidBody::update()
{
    body->getMotionState()->getWorldTransform(physicsTransform);
    auto position = physicsTransform.getOrigin();
    transform->setPosition(position.x(), position.y(), position.z());
}

void RigidBody::draw()
{

}