#ifndef WEBGUI_MALSTUDIO_H
#define WEBGUI_MALSTUDIO_H
#include "../Window/ChildWindow.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vector>

class MalStudio : public ChildWindow {
    public:
        MalStudio(float x, float y, std::string title);
        void Body() override;
        int PlaySound(Mix_Chunk* sound) const;
    private:
        std::vector<Mix_Chunk*> sounds;
        Mix_Chunk* sound;

};


#endif //WEBGUI_MALSTUDIO_H
