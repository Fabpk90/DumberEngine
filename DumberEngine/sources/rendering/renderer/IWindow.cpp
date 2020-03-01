//
// Created by fab on 23/02/2020.
//

#include "../../../headers/rendering/renderer/IWindow.h"

IWindow* IWindow::instance = nullptr;

GLFWwindow *IWindow::getHandle()
{
    return windowHandle;
}