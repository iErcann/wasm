#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <cstdio>

#include "../Window/ChildWindow.h"
#include "MalStudio.h"
#include "imgui.h"
#include <random>



MalStudio::MalStudio(float x, float y, std::string title): ChildWindow(x, y, title){
    SDL_Init(SDL_INIT_AUDIO);
    printf("MalStudio %s\n", title.c_str());
    printf("MalStudio  %s\n", mTitle.c_str());

    const char keys[7] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};

    int c = 0;
    for (int j = 1; j <= 7; j++) {
         for (int i = 0; i < 7; i++) {
            char filePath[20];
             printf("%d: ", ++c);
             std::sprintf(filePath, "../../data/piano/_%c%d.wav", keys[i], j);
             printf("%s\n", filePath);
            sounds.push_back(Mix_LoadWAV(filePath));
        }
    }

}
int MalStudio::PlaySound(Mix_Chunk* sound) const {
    int channel = Mix_PlayChannel(-1, sound, 0);
    return channel;
}

void MalStudio::Body()  {
    std::cout<<"this my body"<<std::endl;
    for (int i = 0; i < sounds.size(); i++){
        ImGui::SameLine(i*70);
        std::string label =  std::to_string(i);
        if (ImGui::Button(label.c_str(), ImVec2(50.0f, 150.0f)))
        {
            PlaySound(sounds[i]);
            printf("Pressed button: %d", i);
        }
    }
    static float begin = 10, end = 90;
    ImGui::DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
}
