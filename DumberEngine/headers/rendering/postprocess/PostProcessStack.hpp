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

class PostProcessStack : GuiComponent, ICallbackResize
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

    Fbo* fbo0;
    GLuint texFBO1;
    GLuint texFBO0;
    GLuint ubo;
    bool isFirstFboBound;

public:
    PostProcessStack();
    ~PostProcessStack();

    void drawInspector() override;

    Fbo& getFBO() { return *fbo0; }
    void addPostProcess(IPostProcess* pp);

    void activateEffects();
    void draw();

public:
    void OnResize(int width, int height) override;

    int getActiveEffects();
};
#endif //DUMBERENGINE_POSTPROCESSSTACK_HPP
