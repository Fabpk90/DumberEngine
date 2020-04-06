//
// Created by fab on 06/04/2020.
//

#include "../../headers/debug/CubeDebug.hpp"

CubeDebug::~CubeDebug()
{
    delete vbo;
}

CubeDebug::CubeDebug(glm::vec3 position)
{
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
    vbo->draw();
}



