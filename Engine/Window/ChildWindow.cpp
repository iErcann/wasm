#include "ChildWindow.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <string>

ChildWindow::ChildWindow(float pX, float pY, std::string pTitle) : bShow(true), mTitle(pTitle), mX(pX), mY(pY)
{
    printf("ChildWindow %s\n", pTitle.c_str());
    printf("ChildWindow %s\n", mTitle.c_str());
}


/*
void ChildWindow::Show(){
    bool showW = true;
    printf("%s\n", mTitle.c_str());
    Body();

    ImGui::Begin(mTitle.c_str(),&showW);
    ImGui::Text("slt");
    ImGui::End();

 }
 */
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