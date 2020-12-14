//
// Created by ncr on 13/12/2020.
//

#ifndef WEBGUI_KEYNOTE_H
#define WEBGUI_KEYNOTE_H
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

struct KeyNote {
    std::string label; // Key label
    int channel; // Played channel
    Mix_Chunk* sound;
    bool pressed;
    int keyCode;
};


#endif //WEBGUI_KEYNOTE_H
