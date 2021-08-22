//
// Created by fab on 15/03/2021.
//

#ifndef DUMBERENGINE_GBUFFER_HPP
#define DUMBERENGINE_GBUFFER_HPP

#include "../IGBuffer.hpp"
#include "Fbo.hpp"

class GBuffer : public IGBuffer, public ICallbackResize
{
public:
    GBuffer(std::vector<IGBuffer::Param>&& params);

    void OnResize(int i, int i1) override;

    void activate() override;

    void bind() override;

    unsigned int getID(Param textureType) override;
    unsigned int getIDFbo() const { return fbo;};

private:
    std::vector<GLuint> textures;
    GLuint fbo;
    std::vector<GLuint> attachmentsList;
};

#endif //DUMBERENGINE_GBUFFER_HPP
