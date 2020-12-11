#include <iostream>
#include <string>

class ChildWindow
{
public:
    ChildWindow(float x, float y, std::string title);
    void Show();
    virtual void Body();
    ~ChildWindow();

private:
    bool bShow;
    std::string mTitle;
    float mX, mY;
};
