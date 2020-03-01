//
// Created by fab on 01/03/2020.
//

#include <glad/glad.h>
#include <stb/stb_image.h>
#include <iostream>
#include "../../../../headers/rendering/renderer/opengl/Texture2D.hpp"

void Texture2D::loadFrom(const char *path)
{
    int width, height, nrChannels;
    unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

    if(data)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        if(nrChannels == 3)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        else if(nrChannels == 4)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "The texture at " << path << " could not be loaded" << std::endl;
    }

    stbi_image_free(data);
}

void Texture2D::use(int textureUnit)
{
    glActiveTexture(textureUnit + GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

Texture2D::~Texture2D()
{
    glDeleteTextures(1, &id);
}
