//
// Created by fab on 19/03/2020.
//

#include <iostream>
#include "../../../../headers/rendering/renderer/opengl/Fbo.hpp"

Fbo::~Fbo()
{
    glDeleteFramebuffers(1, &idFbo);
    glDeleteTextures(1, &idColorTex);
    glDeleteTextures(1, &idDepthTex);
}

void Fbo::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, idFbo);
}

void Fbo::writeToDisk()
{

}

Fbo::Fbo(int width, int height, bool hasDepth, bool hasColor) : IFbo(width, height, hasDepth, hasColor)
{
    glGenFramebuffers(1, &idFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, idFbo);

    if(hasColor)
    {
        glGenTextures(1, &idColorTex);
        glBindTexture(GL_TEXTURE_2D, idColorTex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, idColorTex, 0);

    }

    if(hasDepth)
    {
        glGenTextures(1, &idDepthTex);

        glBindTexture(GL_TEXTURE_2D, idDepthTex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
                     nullptr);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, idDepthTex, 0);
    }

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Ay caramba, framebuffers are not supported by your cg" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void Fbo::enableWrite(bool b)
{

}

void Fbo::enableRead(bool b)
{

}

void Fbo::unBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int Fbo::getColorTexture()
{
    return idColorTex;
}

unsigned int Fbo::getDepthTexture()
{
    return idDepthTex;
}

