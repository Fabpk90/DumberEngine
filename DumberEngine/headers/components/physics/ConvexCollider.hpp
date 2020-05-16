//
// Created by fab on 11/05/2020.
//

#ifndef DUMBERENGINE_CONVEXCOLLIDER_HPP
#define DUMBERENGINE_CONVEXCOLLIDER_HPP

#include "../IComponent.hpp"

class ConvexCollider : public IComponent
{
public:
    void drawInspector() override;

    void start() override;

    void update() override;

    void draw() override;
};
#endif //DUMBERENGINE_CONVEXCOLLIDER_HPP
