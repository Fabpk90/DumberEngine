//
// Created by fab on 09/04/2020.
//

#ifndef DUMBERENGINE_IPOSTPROCESS_HPP
#define DUMBERENGINE_IPOSTPROCESS_HPP

#include <imgui/imgui.h>
#include "../helper/Shader.hpp"
#include "../renderer/opengl/Vbo.hpp"

class IPostProcess
{
protected:
    bool needsDepth;
    bool needsColor;
    bool isActive;

    Shader shader;

    std::string name;

public:
    IPostProcess(const char* shaderPath) : shader(shaderPath)
    {};

    virtual ~IPostProcess() = default;

    bool getNeedColor() { return needsColor;}
    bool getNeedDepth() { return needsDepth;}

    void setActive(bool isActive)
    {
        this->isActive = isActive;
    }
    bool getIsActive() { return isActive;}
    const std::string& getName() { return name;}

    virtual void renderEffect(Vbo* vboToRenderTo) = 0;
    virtual void drawInspector() = 0;
};

#endif //DUMBERENGINE_IPOSTPROCESS_HPP
