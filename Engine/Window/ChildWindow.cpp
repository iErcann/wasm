#include "ChildWindow.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <string>
#include "imgui.h"

ChildWindow::ChildWindow(float pX, float pY, std::string pTitle) : bShow(true), mTitle(pTitle), mX(pX), mY(pY)
{
    printf("ChildWindow %s\n", pTitle.c_str());
    printf("ChildWindow %s\n", mTitle.c_str());
}

void ChildWindow::Show(){
    ImGui::Begin(mTitle.c_str(),&bShow);
    Body();
    ImGui::End();

 }
