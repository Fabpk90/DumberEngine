//
// Created by fab on 01/05/2020.
//

#include "../../headers/debug/TextureDebug.hpp"

TextureDebug::TextureDebug(const char *path) : shader("shaders/quad/")
{
    texture.loadFrom(path, ITexture::Diffuse);
    vboQuad = new Vbo(1, 6);
    vboQuad->setElementDescription(0, Vbo::Element(3));
    vboQuad->createCPUSide();

    vboQuad->setElementData(0, 0, -1, -1, 0);
    vboQuad->setElementData(0, 1, 1, -1, 0);
    vboQuad->setElementData(0, 2, -1, 1, 0);
    vboQuad->setElementData(0, 3, -1, 1, 0);
    vboQuad->setElementData(0, 4, 1, -1, 0);
    vboQuad->setElementData(0, 5, 1, 1, 0);

    vboQuad->createGPUSide();
    vboQuad->deleteCPUSide();
}

void TextureDebug::draw()
{
    texture.use(0);
    shader.use();

    vboQuad->draw();
}

TextureDebug::TextureDebug(GLuint texID, glm::vec2 scale): shader("shaders/quad/")
{
    vboQuad = new Vbo(1, 6);
    vboQuad->setElementDescription(0, Vbo::Element(3));
    vboQuad->createCPUSide();

    vboQuad->setElementData(0, 0, -1 * scale.x, -1 * scale.y, 0);
    vboQuad->setElementData(0, 1, 1 * scale.x, -1 * scale .y, 0);
    vboQuad->setElementData(0, 2, -1 * scale.x, 1 * scale.y, 0);
    vboQuad->setElementData(0, 3, -1 * scale.x, 1 * scale.y, 0);
    vboQuad->setElementData(0, 4, 1 * scale.x, -1 * scale.y, 0);
    vboQuad->setElementData(0, 5, 1 * scale.x, 1 * scale.y, 0);

    vboQuad->createGPUSide();
    vboQuad->deleteCPUSide();

    texture.setID(texID);
}

