#include "ChildWindow.h"
#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"
#include <iostream>
#include <string>

ChildWindow::ChildWindow(float pX, float pY, std::string pTitle) : mX(pX), mY(pY), mTitle(pTitle)
{
    printf("ChildWindow %s\n", pTitle.c_str());
    printf("ChildWindow %s\n", mTitle.c_str());
}

ChildWindow::~ChildWindow()
{
}

 

void ChildWindow::Show()
{
    bool showW = true;
    printf("ChildWindow Title %s\n", mTitle.c_str());
    std::string s = std::to_string(mX);
    ImGui::Begin(s.c_str(),&showW);
    ImGui::Text("slt");
    ImGui::End();

    /*
    ImGui::Begin(mTitle.c_str()+'\0', &showW);
    ImGui::Text("mTitle.c_str()");
    //Body();
    ImGui::End();
    */
    /* ImGui::Text("Hello from another window!");
    if (ImGui::Button("Hi Hat"))
    {
        std::cout << "does it work?" << std::endl;
     }*/ 

}