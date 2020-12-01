#include <iostream>
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include "Engine.h"

namespace MO3D
{
    Engine::Engine() : run(true), window(NULL), videoWidth(800), videoHeight(600)
    {
    }
    void Engine::Initialize()
    {
        if (!glfwInit())
        {
            fprintf(stderr, "Failed to initialize GLFW\n");
        }
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL
    }
    void Engine::Update()
    {
        std::cout << "hi" << std::endl;
    }
    void Engine::Quit()
    {
        run = false;
    }

} // namespace MO3D