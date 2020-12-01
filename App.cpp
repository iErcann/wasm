#include <stdio.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define GLFW_INCLUDE_ES3
#include <GLES3/gl3.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <ctime>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>

#include "Engine/Engine.h"

void loop(){ 
    MO3D::Core.Update();
}
extern "C" int main(int argc, char **argv)
{
    MO3D::Core.Initialize();
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#endif
    MO3D::Core.Quit();
    return 0;
}

 