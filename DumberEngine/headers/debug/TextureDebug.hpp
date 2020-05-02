//
// Created by fab on 01/05/2020.
//

#ifndef DUMBERENGINE_TEXTUREDEBUG_HPP
#define DUMBERENGINE_TEXTUREDEBUG_HPP

#include <glad/glad.h>
#include "../rendering/renderer/opengl/Texture2D.hpp"
#include "../rendering/renderer/opengl/Vbo.hpp"
#include "../rendering/helper/Shader.hpp"

class TextureDebug
{
private:
    Texture2D texture;
    Vbo* vboQuad;
    Shader shader;

public:
    TextureDebug(GLuint texID, glm::vec2 rect);
    TextureDebug(const char* path);

    void draw();

};
#endif //DUMBERENGINE_TEXTUREDEBUG_HPP
