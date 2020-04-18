//
// Created by fab on 13/04/2020.
//

#ifndef DUMBERENGINE_PPOUTLINE_HPP
#define DUMBERENGINE_PPOUTLINE_HPP

#include "IPostProcess.hpp"
#include "../renderer/opengl/Vbo.hpp"

class PPOutline : public IPostProcess
{
private:
    float strength;
public:
    PPOutline(const char* shaderPath);

    void renderEffect(Vbo* vboToRenderTo) override;

    void drawInspector() override;
};
#endif //DUMBERENGINE_PPOUTLINE_HPP
