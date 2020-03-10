//
// Created by fab on 22/02/2020.
//

#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"

#include "glad/glad.h"
#include "glad/glad.c"
#include "glfw/glfw3.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_impl_glfw.h>

#include <string>
#include <iostream>

#include "../headers/rendering/renderer/opengl/OpenGLRenderer.hpp"
#include "../headers/rendering/helper/Shader.hpp"
#include "../headers/rendering/renderer/opengl/Vbo.hpp"
#include "../headers/rendering/renderer/Camera.hpp"
#include "../headers/rendering/helper/Time.hpp"
#include "../headers/rendering/renderer/opengl/InputManager.hpp"
#include "../headers/rendering/Scene.hpp"
#include "../headers/components/GameObject.hpp"
#include "../headers/components/scripts/CameraScript.hpp"
#include "../headers/components/scripts/World.hpp"
#include "../headers/components/Transform.hpp"

#include "bullet/btBulletDynamicsCommon.h"
#include "../headers/Engine.hpp"

GLenum glCheckError_(const char *file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:
                error = "INVALID_ENUM";
                break;
            case GL_INVALID_VALUE:
                error = "INVALID_VALUE";
                break;
            case GL_INVALID_OPERATION:
                error = "INVALID_OPERATION";
                break;
            case GL_OUT_OF_MEMORY:
                error = "OUT_OF_MEMORY";
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                error = "INVALID_FRAMEBUFFER_OPERATION";
                break;
            default:
                error = "AY CARAMBA";
                break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}

#define glCheckError() glCheckError_(__FILE__, __LINE__)


int main(int argc, char **argv)
{
   Engine* engine = new Engine();
   engine->start();
   engine->update();

   delete engine;

   return 0;
}


