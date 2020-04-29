//
// Created by fab on 23/02/2020.
//

#ifndef DUMBERENGINE_IWINDOW_H
#define DUMBERENGINE_IWINDOW_H

#include <glfw/glfw3.h>
#include <vector>
#include <functional>
#include <glm/glm.hpp>

class ICallbackResize
{
public:
    virtual void OnResize(int, int) = 0;
};

struct SWindowData
{
    int width;
    int height;
    char *name;
};

class IWindow
{
public:

    virtual ~IWindow() = default;

    virtual void init(SWindowData data) = 0;

    virtual void closeWindow() = 0;

    virtual int getActualWidth() = 0;
    virtual int getActualHeight() = 0;

    virtual void setSize(int width, int height) = 0;
    virtual void setVSync(bool isActivated) = 0;

    virtual void setFramerate(int framerate) = 0;

    void setClearColor(glm::vec3 color) { clearColor = color; }
    glm::vec3& getClearColor() { return clearColor; }

    virtual void addWindowLoseFocusCallback(std::function<void(bool)>) = 0;
    virtual void addWindowResizeCallback(ICallbackResize* callBack) = 0;

    virtual std::vector<std::function<void(bool)>>& getCallbacksLoseFocus() = 0;
    virtual std::vector<ICallbackResize*>& getCallBacksResize() = 0;

    GLFWwindow* getHandle();

    static IWindow* instance;

protected:
    GLFWwindow* windowHandle = nullptr;
    glm::vec3 clearColor;

};

#endif //DUMBERENGINE_IWINDOW_H