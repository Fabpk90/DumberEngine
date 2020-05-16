//
// Created by fab on 13/04/2020.
//

#include "../../../headers/rendering/postprocess/PPNoParams.hpp"


PPNoParams::PPNoParams(const char *shaderPath, bool isActive) : IPostProcess(shaderPath, isActive)
{
    name = shaderPath;

    uiString = "Enable " + name + " ?";
}

void PPNoParams::drawInspector()
{
    if(ImGui::CollapsingHeader(name.c_str()))
    {
        ImGui::Checkbox(uiString.c_str(), &isActive);
    }

}

void PPNoParams::renderEffect(Vbo* vboToRenderTo)
{
    shader.use();
    unsigned int parameters = glGetUniformBlockIndex(shader.getID(), "globalPPParameters");
    glUniformBlockBinding(shader.getID(), parameters, 0);

    shader.setInt("TexDepth", 1);

    vboToRenderTo->draw();
}


