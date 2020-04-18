//
// Created by fab on 09/04/2020.
//

#ifndef DUMBERENGINE_POSTPROCESSSTACK_HPP
#define DUMBERENGINE_POSTPROCESSSTACK_HPP

#include <list>
#include "IPostProcess.hpp"
#include "../../components/IComponent.hpp"
#include "../renderer/opengl/Vbo.hpp"
#include "../renderer/opengl/Fbo.hpp"

class PostProcessStack : GuiComponent
{
private:
    struct SUniforms
    {
        float screen_width;
        float screen_height;
        glm::vec2 near_far;
    };

private:
    std::list<IPostProcess*> stack;
    Vbo* vboQuad;

    Shader shaderQuad;

    Fbo* fbo;
    GLuint ubo;

public:
    PostProcessStack();
    ~PostProcessStack();

    void drawInspector() override;

    Fbo& getFbo() { return *fbo; }
    void setFbo(Fbo* f) { fbo = f; }
    void addPostProcess(IPostProcess* pp);
    const std::list<IPostProcess*>& getStack() { return stack; }

    void activateEffects();
    void draw();
};
#endif //DUMBERENGINE_POSTPROCESSSTACK_HPP
