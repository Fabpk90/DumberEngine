//
// Created by fab on 19/03/2020.
//

#include <iostream>
#include <stb/stb_image_write.h>

#include <chrono>
#include <time.h>
#include <string>

#include "../../../../headers/rendering/renderer/opengl/Fbo.hpp"
#include "../../../../headers/rendering/renderer/IWindow.h"

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
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string s = "screenshots/";

    time_t t;

    s += std::to_string(time(&t));
    s += ".bmp";

    std::cout << "Saving " << s << std::endl;

    char *data =  new char[width * height * 3]; // 3 components (R, G, B)

    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);

    stbi_flip_vertically_on_write(true);
    stbi_write_bmp(s.c_str(), width, height, 3, data);

    delete[] data;
}

Fbo::Fbo(int width, int height, bool hasDepth, bool hasColor, bool updateOnResize)
: IFbo(width, height, hasDepth, hasColor, updateOnResize)
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

    if( (hasColor || hasDepth) && glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Ay caramba, framebuffers are not supported by your cg" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if(updateOnResize)
    {
        IWindow::instance->addWindowResizeCallback(this);
    }
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

void Fbo::setDepthTexture(unsigned int id)
{
    //if(idDepthTex != -1) handle referencing

    idDepthTex = id;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, idDepthTex, 0);
}

void Fbo::setColorTexture(unsigned int id)
{
    //TODO: handle referencing here as well and bound fbo

    hasColor = true;

    idColorTex = id;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, idColorTex, 0);
}

Fbo::Fbo(int width, int height, int colorTexId, int depthTexId) : IFbo(width, height, colorTexId, depthTexId)
{
    glGenFramebuffers(1, &idFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, idFbo);

    if(colorTexId != -1)
    {
        idColorTex = colorTexId;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, idColorTex, 0);
    }

    if(depthTexId != -1)
    {
        idDepthTex = depthTexId;
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, idDepthTex, 0);
    }
}

void Fbo::OnResize(int width, int height)
{
    this->width = width;
    this->height = height;

    if(hasColor)
    {
        glBindTexture(GL_TEXTURE_2D, idColorTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }

    if(hasDepth)
    {
        glBindTexture(GL_TEXTURE_2D, idDepthTex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE,
                     nullptr);
    }
}
