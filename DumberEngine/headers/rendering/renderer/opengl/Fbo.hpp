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
    Fbo() = delete;
    Fbo(int width, int height, bool hasDepth = true, bool hasColor = false, bool updateOnResize = false);
    Fbo(int width, int height, int colorTexId, int depthTexId);

    ~Fbo() override;

    void bind() override;

    void unBind() override;

    void writeToDisk() override;

    void enableWrite(bool b) override;

    void enableRead(bool b) override;

    unsigned int getColorTexture() override;

    void setColorTexture(unsigned int id) override;

    void setDepthTexture(unsigned int id) override;

    unsigned int getDepthTexture() override;

    unsigned int getID() { return idFbo;}

public:
    void OnResize(int i, int i1) override;

};

#endif //DUMBERENGINE_FBO_HPP
