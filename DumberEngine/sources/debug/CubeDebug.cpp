//
// Created by fab on 06/04/2020.
//

#include "../../headers/debug/CubeDebug.hpp"
#include "../../headers/rendering/renderer/Camera.hpp"

CubeDebug::~CubeDebug()
{
    delete vbo;
}

CubeDebug::CubeDebug(glm::vec3 position) : shader("shaders/cube/"), position(position)
{
    scale = glm::vec3(1.0f);

    vbo = new Vbo(3, 36);

    // Définition du contenu VBO
    vbo->setElementDescription(0, Vbo::Element(3)); //Sommet
    vbo->setElementDescription(1, Vbo::Element(3)); //Normal
    vbo->setElementDescription(2, Vbo::Element(2)); //UV

    vbo->createCPUSide();

    // On ajoute les sommets
    int iVertice = 0;

    // Surface 1
    vbo->setElementData(0, iVertice, 0, 0, 0);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 1
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, 0, -1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;

    // Surface 2
    vbo->setElementData(0, iVertice, 0, 0, 0);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 2
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, -1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;


    // Surface 3
    vbo->setElementData(0, iVertice, 0, 0, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 3
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 0, 0, -1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;


    // Surface 1
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 0);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 1
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 1);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 0, 1, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;


    // Surface 2
    vbo->setElementData(0, iVertice, 1, 0, 0);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 2
    vbo->setElementData(0, iVertice, 1, 1, 0);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 1);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 1, 0, 0);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;


    // Surface 3
    vbo->setElementData(0, iVertice, 0, 0, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    // Surface 3
    vbo->setElementData(0, iVertice, 1, 0, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 1, 1, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);
    ++iVertice;
    vbo->setElementData(0, iVertice, 0, 1, 1);
    vbo->setElementData(1, iVertice, 0, 0, 1);
    vbo->setElementData(2, iVertice, 0, 0);

    vbo->createGPUSide();
    // On envoie le contenu au GPU
    vbo->deleteCPUSide();
}

void CubeDebug::draw()
{
    shader.use();

    glm::mat4 m = glm::mat4(1.0f);
    m[3] = glm::vec4(position, 1.0f);
    m[0][0] = scale.x;
    m[1][1] = scale.y;
    m[2][2] = scale.z;

    shader.setMatrix4("m", m);
    glm::mat4 v = Camera::getInstance().getViewMatrix();
    shader.setMatrix4("v", v);
    auto p = Camera::getInstance().getProjectionMatrix();
    shader.setMatrix4("p", p);

    vbo->draw();
}

void CubeDebug::setPosition(float x, float y, float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void CubeDebug::setPosition(glm::vec3 pos)
{
    position = pos;
}

void CubeDebug::setScale(float x, float y, float z)
{
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

void CubeDebug::setScale(glm::vec3 scale)
{
    this->scale = scale;
}



