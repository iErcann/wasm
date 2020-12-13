#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <cstdio>
#include "imgui.h"

#include "../Window/ChildWindow.h"
#include "MalStudio.h"
#include "KeyNote.h"
#include <random>



MalStudio::MalStudio(float x, float y, std::string title): ChildWindow(x, y, title){
    SDL_Init(SDL_INIT_AUDIO);
    printf("MalStudio %s\n", title.c_str());
    printf("MalStudio  %s\n", mTitle.c_str());

    /*
     * 		} else {
			addKey("a", -1);
			addKey("as", -1);
			addKey("b", -1);
			var notes = "c cs d ds e f fs g gs a as b".split(" ");
			for(var oct = 0; oct < 7; oct++) {
				for(var i in notes) {
					addKey(notes[i], oct);
				}
			}
			addKey("c", 7);
     */


    std::vector<std::string> keys;
    keys.push_back("c");
    keys.push_back("cs");
    keys.push_back("d");
    keys.push_back("ds");
    keys.push_back("e");
    keys.push_back("f");
    keys.push_back("fs");
    keys.push_back("g");
    keys.push_back("gs");
    keys.push_back("a");
    keys.push_back("as");
    keys.push_back("b");

    int c = 0;
    for (int j = 0; j <= 6; j++) {
         for (int i = 0; i < keys.size(); i++) {
             char fileName[20];
             std::sprintf(fileName, "%s%d.wav", keys[i].c_str(), j);
             char filePath[40];
             printf("%d: ", ++c);
             std::sprintf(filePath, "../../data/pianoMPP/%s", fileName);
             printf("%s\n", filePath);
             Mix_Chunk* sound = Mix_LoadWAV(filePath);
             KeyNote keyNote = {
                     .label = fileName,
                     .sound = sound
             };
             keyNotes.push_back(keyNote);

         }
    }

}
int MalStudio::PlaySound(Mix_Chunk* sound) const {
    int channel = Mix_PlayChannel(-1, sound, 0);
    return channel;
}

void MalStudio::Body()  {
    if (ImGui::IsWindowFocused()){
        OnKeyInput();
    }
    for (int i = 0; i < keyNotes.size(); i++){
        ImGui::SameLine(i*30);
        std::string label =  std::to_string(i);
        if (ImGui::Button(keyNotes[i].label.c_str(), ImVec2(25.0f, 150.0f)))
        {
            PlaySound(keyNotes[i].sound);
            printf("Pressed button: %s", keyNotes[i].label.c_str());
        }
    }
    static float begin = 10, end = 90;
    ImGui::DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
}

void MalStudio::OnKeyInput(){
    printf("%s", mTitle);
}
