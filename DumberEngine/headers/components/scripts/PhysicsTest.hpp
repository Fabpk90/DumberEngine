//
// Created by fab on 28/08/2020.
//

#ifndef DUMBERENGINE_PHYSICSTEST_HPP
#define DUMBERENGINE_PHYSICSTEST_HPP

#include "../IComponent.hpp"

class PhysicsTest : public IComponent
{
public:
    void start() override;

    void update() override;

    void draw() override;
};

#endif //DUMBERENGINE_PHYSICSTEST_HPP
