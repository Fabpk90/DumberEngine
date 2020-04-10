//
// Created by fab on 09/04/2020.
//

#ifndef DUMBERENGINE_IPOSTPROCESS_HPP
#define DUMBERENGINE_IPOSTPROCESS_HPP

#include "../helper/Shader.hpp"

class IPostProcess
{
protected:
    bool needsDepth;
    bool needsColor;
    bool isActive;

    Shader shader;

public:
    IPostProcess(const char* shaderPath) : shader(shaderPath)
    {};

    bool getNeedColor() { return needsColor;}
    bool getNeedDepth() { return needsDepth;}

    void setActive(bool isActive) { this->isActive = isActive;}
};

#endif //DUMBERENGINE_IPOSTPROCESS_HPP
