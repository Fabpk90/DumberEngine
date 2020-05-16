//
// Created by fab on 11/05/2020.
//
#include <imgui/imgui.h>
#include "../../../headers/components/physics/BoxCollider.hpp"
#include "../../../headers/systems/physics/Physics.hpp"
#include "../../../headers/rendering/Scene.hpp"
#include "../../../headers/components/physics/RigidBody.hpp"

void BoxCollider::drawInspector()
{
    auto& val = transform.getOrigin().m_floats;
    ImGui::Text("Collider pos: %f %f %f", val[0], val[1], val[2]);
}

void BoxCollider::start()
{
    auto& val = transform.getOrigin().m_floats;
    cube = new CubeDebug(glm::vec3(val[0], val[1], val[2]));

    transform.setIdentity();

    if(!Scene::getGameObject(*gameObjectIndex)->getComponent<RigidBody>())
    {
        isStatic = true;
        transform.setOrigin(btVector3(0.0f, -70.0f, 0.0f));

        mass = btScalar(0.0f);

        btDefaultMotionState* myMotionState = new btDefaultMotionState(transform);
        btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, shape, btVector3(0.0f, 0.0f, 0.0f));
        body = new btRigidBody(rbInfo);

        //rigidbody is dynamic if and only if mass is non zero, otherwise static
        mass = btScalar(0.0f);

        float* scale = shape->getHalfExtentsWithMargin().m_floats;
        cube->setScale(scale[0], scale[1], scale[2]);

        Physics::physicEngine->addRigidBody(body);
    }
    else
        isStatic = false;
}

void BoxCollider::update()
{
    auto& val = transform.getOrigin().m_floats;
    cube->setPosition(glm::vec3(val[0], val[1], val[2]));
}

void BoxCollider::draw()
{
    //TODO: batch this

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    cube->draw();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BoxCollider::setColliderScale(btVector3 scale)
{
    shape->setLocalScaling(scale);
}
