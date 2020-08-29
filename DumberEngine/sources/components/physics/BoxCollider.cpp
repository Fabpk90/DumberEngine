//
// Created by fab on 11/05/2020.
//
#include <imgui/imgui.h>
#include <iostream>
#include "../../../headers/components/physics/BoxCollider.hpp"
#include "../../../headers/rendering/Scene.hpp"
#include "../../../headers/components/physics/RigidBody.hpp"

void BoxCollider::drawInspector()
{
    auto& val = physicsTransform->getOrigin().m_floats;
    ImGui::Text("Collider pos: %f %f %f", val[0], val[1], val[2]);
}

void BoxCollider::start()
{
    cube = new CubeDebug(glm::vec3(0.0f));
    if(!Scene::getGameObject(*gameObjectIndex)->getComponent<RigidBody>())
    {
        physicsTransform = new btTransform();
        physicsTransform->setIdentity();

        btScalar* val = physicsTransform->getOrigin().m_floats;
        cube->setPosition(val[0], val[1], val[2]);

        isStatic = true;
        physicsTransform->setOrigin(btVector3(0.0f, 0.0f, 0.0f));

        mass = btScalar(0.0f);

        btDefaultMotionState* myMotionState = new btDefaultMotionState(*physicsTransform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, btVector3(0.0f, 0.0f, 0.0f));
        body = new btRigidBody(rbInfo);

        body->setUserPointer(gameObjectIndex);

        float* scale = shape->getHalfExtentsWithMargin().m_floats;
        cube->setScale(scale[0], scale[1], scale[2]);

        Physics::physicEngine->addRigidBody(body);
    }
    else
        isStatic = false;
}

void BoxCollider::update()
{
    auto& val = physicsTransform->getOrigin().m_floats;
    cube->setPosition(glm::vec3(val[0], val[1], val[2]));
}

void BoxCollider::draw()
{
    //TODO: batch this

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    cube->draw();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BoxCollider::setColliderScale(btVector3 scale)
{
    shape->setLocalScaling(scale);
    cube->setScale(scale.x(), scale.y(), scale.z());
}
