#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/XTest.h>

/*
Ubuntu need to install: x11proto-dev, libxtst-dev, xdotool
*/

#define LEFT_MOUSE_BUTTON 1
#define RIGHT_MOUSE_BUTTON 3

class Mouse{
    private:
        Display *display;
    public:
        Mouse();
        ~Mouse();
        bool checkIfInit();
        void button_make(unsigned int);
        /* 
            button_*(value): 
            value = 1 - left mouse button
                    3 - right mouse button
        */
        void button_break(unsigned int);
        void move(int, int);
        void setm(int, int);
        void test();
};