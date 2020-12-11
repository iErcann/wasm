#include <iostream>
#include <string>

class ChildWindow
{
public:
    ChildWindow(float x, float y, std::string title)
    {
        mX = pX;
        mY = pY;
        mTitle = pTitle;
    };
    virtual void Body();
    void Show()
    {
        bool showW = true;
        ImGui::Begin(mTitle.c_str(), &showW);
        Body();
        ImGui::End();
    };
    ~ChildWindow();

private:
    bool bShow;
    std::string mTitle;
    float mX, mY;
};
