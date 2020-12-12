#include "ChildWindow.h"
#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <string>

ChildWindow::ChildWindow(float pX, float pY, std::string pTitle) : mX(pX), mY(pY), mTitle(pTitle)
{
    printf("ChildWindow %s\n", pTitle.c_str());
    printf("ChildWindow %s\n", mTitle.c_str());
}

ChildWindow::~ChildWindow()
{
}

 
/*
void ChildWindow::Show()
{

    bool showW = true;
    printf("ChildWindow Title %s\n", mTitle.c_str());

    std::string s = std::to_string(mX);
    ImGui::Begin("s.c_str()",&showW);
    ImGui::Text("slt");
    ImGui::End();


}
*/