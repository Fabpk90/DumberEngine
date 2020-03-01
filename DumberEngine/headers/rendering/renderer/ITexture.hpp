//
// Created by fab on 01/03/2020.
//

#ifndef DUMBERENGINE_ITEXTURE_HPP
#define DUMBERENGINE_ITEXTURE_HPP

class ITexture
{
public:
    virtual void loadFrom(const char* path) = 0;
    virtual void use() = 0;


    virtual ~ITexture() = 0;
};

#endif //DUMBERENGINE_ITEXTURE_HPP
