//
// Created by fab on 23/02/2020.
//

#ifndef DUMBERENGINE_OPENGLRENDERER_HPP
#define DUMBERENGINE_OPENGLRENDERER_HPP

#include <glm/vec2.hpp>
#include <vector>
#include <functional>
#include "../IWindow.h"

class OpenGLRenderer : public IWindow
{
private:
    glm::vec2 windowSize;
    static void resizeCallback(GLFWwindow *window, int width, int height);
    std::vector<std::function<void(bool)>> callbacksWindowLoseFocus;
    std::vector<ICallbackResize*> callbacksWindowResize;

public:
    ~OpenGLRenderer() override;

    void init(SWindowData data) override;

    void closeWindow() override;

    int getActualWidth() override;

    int getActualHeight() override;

    void setVSync(bool isActivated) override;

    void setFramerate(int framerate) override;

    void addWindowLoseFocusCallback(std::function<void(bool)>) override;

    void addWindowResizeCallback(ICallbackResize* callBack) override;

    std::vector<std::function<void(bool)>> &getCallbacksLoseFocus() override;

    std::vector<ICallbackResize*> &getCallBacksResize() override;

    void setSize(int width, int height) override;
};

#endif //DUMBERENGINE_OPENGLRENDERER_HPP
