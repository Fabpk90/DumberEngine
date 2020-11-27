//
// Created by fab on 25/11/2020.
//

#ifndef DUMBERENGINE_EDITOR_HPP
#define DUMBERENGINE_EDITOR_HPP

#include <vector>
#include <glfw/glfw3.h>
#include <iostream>
#include "ISystem.hpp"
#include "../utils/IDragNDrop.hpp"

class Editor : public ISystem
{
private:
    std::vector<IDragNDrop*> callbackDragNDrop;

public:
    static Editor* instance;

public:
    void init() override;

    void update() override;

    std::vector<IDragNDrop*>& getDragNDropCallbacks() { return callbackDragNDrop;}

    static void onDroppedFile(GLFWwindow* window, int count, const char** paths)
    {
        for(auto callback : Editor::instance->getDragNDropCallbacks())
        {
            for (int i = 0;  i < count;  i++)
                callback->OnFileDropped(paths[i]);
        }
    }

    void addDragNDropCallback(IDragNDrop* callback)
    {
        callbackDragNDrop.push_back(callback);
    }

    void removeDragNDropCallback(IDragNDrop* callback)
    {
        auto index = std::find(callbackDragNDrop.begin(), callbackDragNDrop.end(), callback);
        callbackDragNDrop.erase(index);
    }
};

#endif //DUMBERENGINE_EDITOR_HPP
