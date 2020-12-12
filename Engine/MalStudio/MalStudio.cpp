#include "MalStudio.h"
#include "imgui.h"
#include "../imgui_impl_glfw.h"
#include "../imgui_impl_opengl3.h"


MalStudio::MalStudio(float x, float y, std::string title): ChildWindow(x, y, title){
    printf("MalStudio %s\n", title.c_str());
    printf("MalStudio  %s\n", mTitle.c_str());
}
void MalStudio::Body()  {
    std::cout<<"this my body"<<std::endl;
}
