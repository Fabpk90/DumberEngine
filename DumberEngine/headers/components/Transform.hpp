//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_TRANSFORM_HPP
#define DUMBERENGINE_TRANSFORM_HPP

#include "IComponent.hpp"

class Transform : public IComponent
{
    void start() override;

    void update() override;

    void draw() override;

    void drawInspector() override;
};

#endif //DUMBERENGINE_TRANSFORM_HPP
