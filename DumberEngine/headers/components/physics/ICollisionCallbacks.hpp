//
// Created by fab on 28/08/2020.
//

#ifndef DUMBERENGINE_ICOLLISIONCALLBACKS_HPP
#define DUMBERENGINE_ICOLLISIONCALLBACKS_HPP

#include <glm/glm.hpp>

class ICollisionCallbacks
{
public:
    virtual void onCollisionEnter(ICollisionCallbacks* other, glm::vec3 point) = 0;
    virtual void onCollisionStay(ICollisionCallbacks* other, glm::vec3 point) = 0;
    virtual void onCollisionExit() = 0;
};

#endif //DUMBERENGINE_ICOLLISIONCALLBACKS_HPP
