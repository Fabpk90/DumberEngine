//
// Created by fab on 23/02/2020.
//

#ifndef DUMBERENGINE_IWINDOW_H
#define DUMBERENGINE_IWINDOW_H

#include <glfw/glfw3.h>

struct SWindowData
{
    int width;
    int height;
    char* name;
};

class IWindow
{
public:


    virtual ~IWindow() = default;

    virtual void init(SWindowData data) = 0;
    virtual void release() = 0;

    GLFWwindow* GetHandle();

protected:
    GLFWwindow* windowHandle = nullptr;
};

#endif //DUMBERENGINE_IWINDOW_H