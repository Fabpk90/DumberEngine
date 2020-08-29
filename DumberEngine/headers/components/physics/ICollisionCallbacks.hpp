//
// Created by fab on 28/08/2020.
//

#ifndef DUMBERENGINE_ICOLLISIONCALLBACKS_HPP
#define DUMBERENGINE_ICOLLISIONCALLBACKS_HPP

#include <glm/glm.hpp>

class GameObject;

class ICollisionCallbacks
{
public:
    virtual void onCollisionEnter(GameObject* other, glm::vec3 point){};
    virtual void onCollisionStay(GameObject* other, glm::vec3 point){};
    virtual void onCollisionExit(){};
};

#endif //DUMBERENGINE_ICOLLISIONCALLBACKS_HPP
