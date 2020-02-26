//
// Created by fab on 25/02/2020.
//

#ifndef DUMBERENGINE_CAMERASCRIPT_HPP
#define DUMBERENGINE_CAMERASCRIPT_HPP

#include "../IComponent.hpp"
#include "../../rendering/renderer/Camera.hpp"

class CameraScript : public IComponent
{
private:
    bool isCursorvisible;
    bool isRightButtonReleased;
public:
    CameraScript();

    ~CameraScript() override;

    void start() override;

    void update() override;

    void draw() override;
};

#endif //DUMBERENGINE_CAMERASCRIPT_HPP
