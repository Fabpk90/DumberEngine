//
// Created by fab on 22/02/2020.
//

#define STB_IMAGE_IMPLEMENTATION

#include "stb/stb_image.h"


#include "glad/glad.c"
#include "glfw/glfw3.h"


#include <string>
#include <iostream>

#include "../headers/rendering/renderer/opengl/OpenGLRenderer.hpp"
#include "../headers/rendering/renderer/opengl/InputManager.hpp"

#include "../headers/Engine.hpp"


int main(int argc, char **argv)
{
   Engine* engine = new Engine();
   engine->start();
   engine->update();

   delete engine;

   return 0;
}


