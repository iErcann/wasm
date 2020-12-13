#include "../Window/ChildWindow.h"
#include "MalStudio.h"


MalStudio::MalStudio(float x, float y, std::string title): ChildWindow(x, y, title){
    printf("MalStudio %s\n", title.c_str());
    printf("MalStudio  %s\n", mTitle.c_str());
}
void MalStudio::Body()  {
    std::cout<<"this my body"<<std::endl;
}
void MalStudio::Show(){
    std::cout<<"this my show"<<std::endl;
}