//
// Created by fab on 05/12/2020.
//

#ifndef DUMBERENGINE_SKYBOX_HPP
#define DUMBERENGINE_SKYBOX_HPP

#include "../IComponent.hpp"
#include "../../rendering/renderer/opengl/Texture2D.hpp"

class SkyBox : public IComponent
{
private:
    Texture2D* tex;

public:
    void start() override;

    void draw() override;

    void drawInspector() override;
};

#endif //DUMBERENGINE_SKYBOX_HPP
