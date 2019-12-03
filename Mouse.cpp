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
    if(display == nullptr)
    {
        return false;
    }
    s = DefaultScreenOfDisplay(display);
    limitX = s->height;
    limitY = s->width;
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
    if((x >= limitX) || (y >= limitY) || (x <= 0) || (y <= 0))
    {
        ;
    }
    else
    {
        XTestFakeMotionEvent(display, 0, x, y, 0);
        XFlush(display);
    }
}

void Mouse::test()
{
    setm(0, 0);
    move(100, 100);
    button_make(RIGHT_MOUSE_BUTTON);
    button_break(RIGHT_MOUSE_BUTTON);
    std::cout << "Screen Height: " << s->height << " Width: " << s->width << std::endl;
    // Cannot test on the VBox with integration drivers
    // below moves the pointer by the offsets (dest_x, dest_y)
    // relative to the current position of the pointer.
    // XWarpPointer(display, None, None, 0, 0, 0, 0, 10, 10); // Or use xdotool mousemove x y
    // XFlush(display);
}
