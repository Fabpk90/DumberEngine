//
// Created by fab on 01/03/2020.
//

#ifndef DUMBERENGINE_ITEXTURE_HPP
#define DUMBERENGINE_ITEXTURE_HPP

class ITexture
{
public:
    virtual void loadFrom(const char* path) = 0;
    virtual void use(int textureUnit) = 0;


    virtual ~ITexture() {};
};

#endif //DUMBERENGINE_ITEXTURE_HPP
