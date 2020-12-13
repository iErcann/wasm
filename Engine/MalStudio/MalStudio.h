#ifndef WEBGUI_MALSTUDIO_H
#define WEBGUI_MALSTUDIO_H
#include "../Window/ChildWindow.h"
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <vector>
#include "KeyNote.h"

class MalStudio : public ChildWindow {
    public:
        MalStudio(float x, float y, std::string title);
        void Body() override;
        int PlaySound(KeyNote keynote) const;
        void OnKeyInput();

    private:
        std::vector<KeyNote> keyNotes;

};


#endif //WEBGUI_MALSTUDIO_H
