//
// Created by fab on 23/02/2020.
//

#ifndef DUMBERENGINE_OPENGLRENDERER_HPP
#define DUMBERENGINE_OPENGLRENDERER_HPP

#include <glm/vec2.hpp>
#include "../IWindow.h"

class OpenGLRenderer : public IWindow
{
private:
    glm::vec2 windowSize;
    static void resizeCallback(GLFWwindow *window, int width, int height);

public:
    ~OpenGLRenderer() override;

    void init(SWindowData data) override;

    void closeWindow() override;

    void release() override;

    int getActualWidth() override;

    int getActualHeight() override;

    void setVSync(bool isActivated) override;

    void setSize(int width, int height) override;
};

#endif //DUMBERENGINE_OPENGLRENDERER_HPP
