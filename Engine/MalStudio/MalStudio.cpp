#include "../Window/ChildWindow.h"
#include "MalStudio.h"
#include "imgui.h"


MalStudio::MalStudio(float x, float y, std::string title): ChildWindow(x, y, title){
    printf("MalStudio %s\n", title.c_str());
    printf("MalStudio  %s\n", mTitle.c_str());
}
void MalStudio::Body()  {
    std::cout<<"this my body"<<std::endl;
    for (int i = 0; i < 10; i++){
        if (ImGui::Button("Save"))
        {
            printf("Pressed button: %d", i);
        }
    }
    static float begin = 10, end = 90;
    ImGui::DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
}
