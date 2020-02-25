//
// Created by fab on 23/02/2020.
//

#ifndef DUMBERENGINE_OPENGLRENDERER_HPP
#define DUMBERENGINE_OPENGLRENDERER_HPP

#include "../IWindow.h"

class OpenGLRenderer : public IWindow
{
public:
    ~OpenGLRenderer() override;

    void init(SWindowData data) override;

    void closeWindow() override;

    void release() override;
};

#endif //DUMBERENGINE_OPENGLRENDERER_HPP
