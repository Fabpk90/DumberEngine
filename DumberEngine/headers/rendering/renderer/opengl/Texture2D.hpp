//
// Created by fab on 01/03/2020.
//

#ifndef DUMBERENGINE_TEXTURE2D_HPP
#define DUMBERENGINE_TEXTURE2D_HPP

#include <gl/GL.h>
#include <glm/glm.hpp>
#include "../ITexture.hpp"

class Texture2D : public ITexture
{
private:
    GLuint id;
    glm::vec2 size;


public:
    bool loadFrom(const char *path, ETextureType type, unsigned int flagWrapS = GL_REPEAT, unsigned int flagWrapT = GL_REPEAT, unsigned int flagMinFilter = GL_NEAREST,
                  unsigned int flagMagFilter = GL_NEAREST) override;

    void use(int textureUnit) override;

    Texture2D() = default;

    Texture2D(const Texture2D& t) = default;
    Texture2D(Texture2D&& t) = default;
    Texture2D& operator=(Texture2D&&) = default;
    Texture2D& operator=(Texture2D&) = default;
    ~Texture2D() override;

    void setID(GLuint id);
    GLuint getID() { return id; }

    const glm::vec2& getSize() { return size; }
};

#endif //DUMBERENGINE_TEXTURE2D_HPP
