#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

#include <iostream>

/*
Ubuntu need to install: libxtst-dev, xdotool
*/

#define LEFT_MOUSE_BUTTON 1
#define RIGHT_MOUSE_BUTTON 3

class Mouse{
    private:
        Display *display;
        Screen *s;
        int limitX;
        int limitY;
        int currentX;
        int currentY;
        int move(int, int);

    public:
        Mouse();
        ~Mouse();
        bool initMouseModule();
        void button_make(unsigned int);
        /*
            button_*(value):
            value = 1 - left mouse button
                    3 - right mouse button
        */
        void button_break(unsigned int);
        int setm(int, int);
        void updateCursorPosition(int, int);
        void test();
};
