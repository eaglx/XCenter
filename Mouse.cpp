#include "Mouse.hpp"

Mouse::Mouse()
{
    display = XOpenDisplay(NULL);
}

Mouse::~Mouse()
{
    if(display != NULL) XCloseDisplay(display);
}

bool Mouse::initMouseModule()
{
    if(display == nullptr)
    {
        return false;
    }
    s = DefaultScreenOfDisplay(display);
    limitY = s->height;
    limitX = s->width;
    currentX = static_cast<int>(limitX/2);
    currentY = static_cast<int>(limitY/2);
    setm(currentX, currentY);
    return true;
}

int Mouse::move(int x, int y)
{
    if((x > limitX) || (y > limitY) || (x < 0) || (y < 0))
    {
        return -1;
    }
    else
    {
        XTestFakeRelativeMotionEvent(display, x, y, 0);
        XFlush(display);
        return 1;
    }
}

void Mouse::updateCursorPosition(int addX, int addY)
{
    if(move(currentX + addX, currentY + addY) == 1)
    {
        currentX += addX;
        currentY += addY;
    }
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


int Mouse::setm(int x, int y)
{
    if((x > limitX) || (y > limitY) || (x < 0) || (y < 0))
    {
        return -1;
    }
    else
    {
        XTestFakeMotionEvent(display, 0, x, y, 0);
        XFlush(display);
        return 1;
    }
}

void Mouse::test()
{
    if(setm(0, 0) == 1) std::cout << "setm() PASS" << std::endl;
    else std::cout << "setm() FAILED" << std::endl;
    if(move(1910, 100) == 1) std::cout << "move() PASS" << std::endl;
    else std::cout << "move() FAILED" << std::endl;
    button_make(RIGHT_MOUSE_BUTTON);
    button_break(RIGHT_MOUSE_BUTTON);
    std::cout << "Screen Height: " << s->height << " Width: " << s->width << std::endl;
    // Cannot test on the VBox with integration drivers
    // below moves the pointer by the offsets (dest_x, dest_y)
    // relative to the current position of the pointer.
    // XWarpPointer(display, None, None, 0, 0, 0, 0, 10, 10); // Or use xdotool mousemove x y
    // XFlush(display);
}
