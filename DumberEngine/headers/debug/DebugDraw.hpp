//
// Created by fab on 31/08/2020.
//

#ifndef DUMBERENGINE_DEBUGDRAW_HPP
#define DUMBERENGINE_DEBUGDRAW_HPP

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "../rendering/helper/Shader.hpp"
#include "../rendering/renderer/Camera.hpp"

class DebugDraw
{
private:
    Shader* shaderDebug = nullptr;
    Vbo* vbo = nullptr;
public:
    static DebugDraw* instance;

public:

    static DebugDraw& GetInstance()
    {
        if(instance == nullptr)
        {
            instance = new DebugDraw();
        }

        return *instance;
    }

    void DrawLine(glm::vec3 from, glm::vec3 to, glm::vec3 color);

};



#endif //DUMBERENGINE_DEBUGDRAW_HPP
