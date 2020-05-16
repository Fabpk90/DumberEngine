//
// Created by fab on 13/04/2020.
//

#ifndef DUMBERENGINE_PPNOPARAMS_HPP
#define DUMBERENGINE_PPNOPARAMS_HPP

#include "IPostProcess.hpp"
#include "../renderer/opengl/Vbo.hpp"

class PPNoParams : public IPostProcess
{
private:
    float strength;
    std::string uiString;
public:
    PPNoParams(const char* shaderPath, bool isActive = false);

    void renderEffect(Vbo* vboToRenderTo) override;

    void drawInspector() override;
};
#endif //DUMBERENGINE_PPNOPARAMS_HPP
