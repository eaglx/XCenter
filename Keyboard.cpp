#include "Keyboard.hpp"

Keyboard::Keyboard()
{
    display = XOpenDisplay (NULL);
}

Keyboard::~Keyboard()
{
    if(display != NULL) XCloseDisplay(display);
}

bool Keyboard::initKeyboardModule()
{
    if(display == nullptr)
    {
        return false;
    }
    return true;
}

void Keyboard::SendKey (Display * disp, KeySym keysym, KeySym modsym)
{
    KeyCode keycode = 0, modcode = 0;
    keycode = XKeysymToKeycode (disp, keysym);
    if (keycode == 0) return;
    XTestGrabControl (disp, True);
    
    /* Generate modkey press */
    if (modsym != 0) 
    {
        modcode = XKeysymToKeycode(disp, modsym);
        XTestFakeKeyEvent (disp, modcode, True, 0);
    }
    
    /* Generate regular key press and release */
    XTestFakeKeyEvent (disp, keycode, True, 0);
    XTestFakeKeyEvent (disp, keycode, False, 0); 

    /* Generate modkey release */
    if (modsym != 0)
        XTestFakeKeyEvent (disp, modcode, False, 0);

    XSync (disp, False);
    XTestGrabControl (disp, False);
}

void Keyboard::wrtieToCurrentWindow(char chr)
{
    SendKey(display, XK_A, 0);
}
