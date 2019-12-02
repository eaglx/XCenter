#include <iostream>
#include "Mouse.hpp"
/*
Ubuntu need: x11proto-dev, libxtst-dev
*/

int main(int argc, char **argv)
{
    std::cout << "TEST" << std::endl;

    Mouse *m = new Mouse();

    if(!m->checkIfInit()) {
        std::cout << "ERROR: FAILED TO INIT Mouse MODULE!" << std::endl;
        goto MAIN_END;
    }

     m->test();

MAIN_END:
    delete m;
    return 0;
}