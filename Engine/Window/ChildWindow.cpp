#include "ChildWindow.h"
#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"
#include <iostream>
#include <string>

ChildWindow::ChildWindow(float pX, float pY, std::string pTitle)
{
    mX = pX;
    mY = pY;
    mTitle = pTitle;
}

ChildWindow::~ChildWindow()
{
}

 

void ChildWindow::Show()
{
    bool showW = true;
    ImGui::Begin(mTitle.c_str(), &showW);
    Body();    
    ImGui::End();
    /* ImGui::Text("Hello from another window!");
    if (ImGui::Button("Hi Hat"))
    {
        std::cout << "does it work?" << std::endl;
     }*/ 

}