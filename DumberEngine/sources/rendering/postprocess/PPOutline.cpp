//
// Created by fab on 13/04/2020.
//

#include "../../../headers/rendering/postprocess/PPOutline.hpp"


PPOutline::PPOutline(const char *shaderPath) : IPostProcess(shaderPath)
{
    name = shaderPath;
}

void PPOutline::drawInspector()
{
    IPostProcess::drawInspector();
}

void PPOutline::renderEffect(Vbo* vboToRenderTo)
{
    shader.use();
    unsigned int parameters = glGetUniformBlockIndex(shader.getID(), "globalPPParameters");
    glUniformBlockBinding(shader.getID(), parameters, 0);

    shader.setInt("TexDepth", 1);

    vboToRenderTo->draw();
}

