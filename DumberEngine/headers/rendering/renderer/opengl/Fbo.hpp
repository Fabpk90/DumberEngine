//
// Created by fab on 19/03/2020.
//

#ifndef DUMBERENGINE_FBO_HPP
#define DUMBERENGINE_FBO_HPP

#include <glad/glad.h>
#include "../IFbo.hpp"

class Fbo : public IFbo
{
protected:
    GLuint idFbo;
    GLuint idColorTex;
    GLuint idDepthTex;
public:

    Fbo(int width, int height, bool hasDepth = true, bool hasColor = false);

    ~Fbo() override;

    void bind() override;

    void unBind() override;

    void writeToDisk() override;

    void enableWrite(bool b) override;

    void enableRead(bool b) override;

    unsigned int getColorTexture() override;

    unsigned int getDepthTexture() override;

};

#endif //DUMBERENGINE_FBO_HPP