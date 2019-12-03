/*
ATTENTION:
XSendEvent doesn't work because many applications discard fake keyboard events by XSendEvent
*/

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

/*
sudo apt-get install libxdo-dev libxdo2
g++ -lxdo
*/

class Keyboard{
    private:
        //xdo_t *xdo;
    public:
        Keyboard();
        ~Keyboard();
        void wrtieToCurrentWindow(char);
};
