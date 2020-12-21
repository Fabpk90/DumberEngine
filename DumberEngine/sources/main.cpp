//
// Created by fab on 22/02/2020.
//

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

//Ugly hax
#include "glad/glad.c"
#include "glfw/glfw3.h"


#include "../headers/Engine.hpp"

int main(int argc, char **argv)
{

   Engine* engine = new Engine();
   engine->start();
   engine->update();

   delete engine;

   return 0;
}


