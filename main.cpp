#include <iostream>
#include <memory>
#include <cstdlib>
#include "Mouse.hpp"


int main(int argc, char **argv)
{
    std::cout << "dev-center-rpi v0.1" << std::endl;

    int srvport;
    int srvbacksize;

    if(argc == 3) {
        srvport = atoi(argv[1]);
        srvbacksize = atoi(argv[2]);
    }

    

    return 0;
}
