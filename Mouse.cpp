#include "Mouse.hpp"

Mouse::Mouse()
{
    display = XOpenDisplay(NULL);
}

Mouse::~Mouse()
{
    if(display != NULL) XCloseDisplay(display);
}

bool Mouse::checkIfInit() 
{
    if(display == NULL) return false;
    return true;
}

void Mouse::move(int x, int y) 
{
    XTestFakeRelativeMotionEvent(display, x, y, 0);
    XFlush(display);
}

void Mouse::button_make(unsigned int button)
{
    XTestFakeButtonEvent(display, button, true, 0);
    XFlush(display);
}

void Mouse::button_break(unsigned int button)
{
    XTestFakeButtonEvent(display, button, false, 0);
    XFlush(display);
}


void Mouse::setm(int x, int y) 
{
    XTestFakeMotionEvent(display, 0, x, y, 0);
    XFlush(display);
}

void Mouse::test() 
{
    setm(0, 0);
    move(100, 100);
    button_make(RIGHT_MOUSE_BUTTON);
    button_break(RIGHT_MOUSE_BUTTON);
}