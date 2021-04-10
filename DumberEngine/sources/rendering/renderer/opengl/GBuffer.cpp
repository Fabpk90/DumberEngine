//
// Created by fab on 15/03/2021.
//

#include <utility>
#include <vector>
#include <iostream>
#include "../../../../headers/rendering/renderer/opengl/GBuffer.hpp"


GBuffer::GBuffer(std::vector<Param>&& params)
{
    isActive = false;
    descriptor = std::move(params);

    const int width = IWindow::instance->getActualWidth();
    const int height = IWindow::instance->getActualHeight();

    textures.reserve(descriptor.size());
    attachmentsList.reserve(descriptor.size());

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    int colorAttachment = -1;
    GLuint idTexture = -1;
    for(const auto& desc : descriptor)
    {
        colorAttachment++;

        glGenTextures(1, &idTexture);
        glBindTexture(GL_TEXTURE_2D, idTexture);

        switch (desc)
        {
            case IGBuffer::Param::Position:
            case IGBuffer::Param::Normal:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachment, GL_TEXTURE_2D, idTexture, 0);
                attachmentsList.emplace_back(GL_COLOR_ATTACHMENT0 + colorAttachment);
                break;
            case IGBuffer::Param::Albedo:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachment, GL_TEXTURE_2D, idTexture, 0);
                attachmentsList.emplace_back(GL_COLOR_ATTACHMENT0 + colorAttachment);
                break;
            case IGBuffer::Param::Depth:
                glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, width, height, 0, GL_R32F, GL_FLOAT, nullptr);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, idTexture, 0);
                attachmentsList.emplace_back(GL_DEPTH_ATTACHMENT);
               break;

            default:
                glDeleteTextures(1, &idTexture);
        }
        textures.emplace_back(idTexture);

        glDrawBuffers(3, attachmentsList.data());

        unsigned int rboDepth;
        glGenRenderbuffers(1, &rboDepth);
        glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            std::cout << "Framebuffer not complete!" << std::endl;
    }
}

void GBuffer::OnResize(int i, int i1)
{

}

void GBuffer::activate()
{
    isActive = true;
    glDrawBuffers(3, attachmentsList.data());
}

void GBuffer::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

unsigned int GBuffer::getID(Param textureType)
{
    for (int i = 0; i < descriptor.size(); ++i)
    {
        if(descriptor[i] == textureType)
        {
            return textures[i];
        }
    }

    return -1;
}
