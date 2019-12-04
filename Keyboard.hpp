#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>


class Keyboard{
    private:
        void SendKey (Display*, KeySym, KeySym);
        Display *display;
    public:
        Keyboard();
        ~Keyboard();
        void wrtieToCurrentWindow(char);
        bool initKeyboardModule();
};
