
#ifndef WEBGUI_CHILDWINDOW_H
#define WEBGUI_CHILDWINDOW_H

#include <iostream>
#include <string>

class ChildWindow
{
public:
    explicit ChildWindow(float x, float y, std::string title);
    void Show();
    virtual void Body() = 0;
    virtual ~ChildWindow() = 0;

public:
    bool bShow;
    std::string mTitle;
    float mX, mY;
};

#endif