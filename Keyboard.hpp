/*
ATTENTION:
XSendEvent doesn't work because many applications discard fake keyboard events by XSendEvent
*/

#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>

/*
sudo apt-get install libxdo-dev libxdo2

#include <stdio.h>
#include <stdlib.h>
#include <xdo.h>
#include <unistd.h>
int main() {
    xdo_t * x = xdo_new(":0.0");

    while(1) {
        printf("simulating Shift_L keypress\n");
        xdo_keysequence(x, CURRENTWINDOW, "Shift_L", 0);
        sleep(5);
    }

        return 0; 
}

g++ -lxdo

*/