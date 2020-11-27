//
// Created by fab on 01/03/2020.
//

#ifndef DUMBERENGINE_ITEXTURE_HPP
#define DUMBERENGINE_ITEXTURE_HPP

#include <assimp/material.h>

class ITexture
{
public:
    enum ETextureType
    {
        Diffuse,
        Specular,
        Albedo,
        Normal,
        Metalness,
        AO,
        Roughness,
        Unknown
    };

    static ETextureType convertFrom(aiTextureType type)
    {
        switch(type)
        {
            case aiTextureType_NONE:
                return Unknown;
            case aiTextureType_DIFFUSE:
                return Diffuse;
            case aiTextureType_SPECULAR:
                return Specular;
            case aiTextureType_AMBIENT:
                break;
            case aiTextureType_EMISSIVE:
                break;
            case aiTextureType_HEIGHT:
                return Specular;
            case aiTextureType_NORMALS:
                return Normal;
            case aiTextureType_SHININESS:
                break;
            case aiTextureType_OPACITY:
                break;
            case aiTextureType_DISPLACEMENT:
                break;
            case aiTextureType_LIGHTMAP:
                break;
            case aiTextureType_REFLECTION:
                break;
            case aiTextureType_BASE_COLOR:
                return Albedo;
            case aiTextureType_NORMAL_CAMERA:
                break;
            case aiTextureType_EMISSION_COLOR:
                break;
            case aiTextureType_METALNESS:
                return Metalness;
            case aiTextureType_DIFFUSE_ROUGHNESS:
                return Roughness;
            case aiTextureType_AMBIENT_OCCLUSION:
                return AO;
            case aiTextureType_UNKNOWN:
                break;
            case _aiTextureType_Force32Bit:
                break;
        }

        return Unknown;
    }

protected:
    ETextureType type;
    std::string name;

public:
    virtual bool loadFrom(const char *path, ETextureType type, unsigned int flagWrapS, unsigned int flagWrapT, unsigned int flagMinFilter,
                          unsigned int flagMagFilter) = 0;
    virtual void use(int textureUnit) = 0;

    ETextureType getType() { return type; }
    std::string& getName() { return name;}


    virtual ~ITexture() {};
};

#endif //DUMBERENGINE_ITEXTURE_HPP
