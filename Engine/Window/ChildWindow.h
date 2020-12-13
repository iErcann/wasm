
#ifndef WEBGUI_CHILDWINDOW_H
#define WEBGUI_CHILDWINDOW_H

#include <iostream>
#include <string>

class ChildWindow
{
public:
    ChildWindow(float x, float y, std::string title);
    virtual void Show() = 0;
    virtual void Body() = 0;
public:
    bool bShow;
    std::string mTitle;
    float mX, mY;
};

#endif