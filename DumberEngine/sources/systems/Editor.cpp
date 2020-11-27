//
// Created by fab on 25/11/2020.
//

#include "../../headers/systems/Editor.hpp"
#include "../../headers/rendering/renderer/IWindow.h"

Editor* Editor::instance = nullptr;

void Editor::init()
{
    instance = this;

    glfwSetDropCallback(IWindow::instance->getHandle(), Editor::onDroppedFile);
}

void Editor::update()
{

}
