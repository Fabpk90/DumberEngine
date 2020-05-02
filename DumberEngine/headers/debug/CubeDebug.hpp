//
// Created by fab on 06/04/2020.
//

#ifndef DUMBERENGINE_CUBEDEBUG_HPP
#define DUMBERENGINE_CUBEDEBUG_HPP

#include <glm/vec3.hpp>
#include "../rendering/renderer/opengl/Vbo.hpp"
#include "../rendering/helper/Shader.hpp"

class CubeDebug
{
private:
    Vbo* vbo;
    Shader shader;
    glm::vec3 position;

public:
    CubeDebug(glm::vec3 position);

    void draw();

    ~CubeDebug();
};
#endif //DUMBERENGINE_CUBEDEBUG_HPP
