//
// Created by fab on 01/03/2020.
//

#ifndef DUMBERENGINE_TEXTURE2D_HPP
#define DUMBERENGINE_TEXTURE2D_HPP

#include <gl/GL.h>
#include "../ITexture.hpp"

class Texture2D : public ITexture
{
private:
    GLuint id;

public:
    void loadFrom(const char *path, unsigned int flagWrapS = GL_REPEAT, unsigned int flagWrapT = GL_REPEAT, unsigned int flagMinFilter = GL_NEAREST,
                  unsigned int flagMagFilter = GL_NEAREST) override;

    void use(int textureUnit) override;

    ~Texture2D() override;
};

#endif //DUMBERENGINE_TEXTURE2D_HPP
