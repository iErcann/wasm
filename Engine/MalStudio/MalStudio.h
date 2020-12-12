#ifndef WEBGUI_MALSTUDIO_H
#define WEBGUI_MALSTUDIO_H
#include "../Window/ChildWindow.h"
#include "MalStudio.h"


class MalStudio : public ChildWindow {
    public:
        MalStudio(float x, float y, std::string title);
        void Body() override;
};


#endif //WEBGUI_MALSTUDIO_H
