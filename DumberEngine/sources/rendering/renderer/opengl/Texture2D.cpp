//
// Created by fab on 01/03/2020.
//

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>
#include "../../../../headers/rendering/renderer/opengl/Texture2D.hpp"

bool Texture2D::loadFrom(const char *path, ETextureType type, unsigned int flagWrapS, unsigned int flagWrapT, unsigned int flagMinFilter,
                         unsigned int flagMagFilter)
{
    this->type = type;

    std::cout << "Loading texture " << path << std::endl;

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    if(data)
    {
        name = path;
        size.x = width;
        size.y = height;

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, flagWrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, flagWrapT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, flagMinFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, flagMagFilter);

        if(nrChannels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if(nrChannels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        else
        {
            std::cout << "The texture has an unknown number of channels" << std::endl;
            return false;
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "The texture at " << path << " could not be loaded" << std::endl;
        return false;
    }

    stbi_image_free(data);
    return true;
}

void Texture2D::use(int textureUnit)
{
    glActiveTexture(textureUnit + GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

Texture2D::~Texture2D()
{
    std::cout << "deleting texture id: " << id << std::endl;
    glDeleteTextures(1, &id);
}

void Texture2D::setID(GLuint id)
{
    this->id = id;
}
