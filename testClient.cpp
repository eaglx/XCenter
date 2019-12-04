#include "Server.hpp"

#include <netinet/in.h>
#include <arpa/inet.h>

/*
g++ -Wall -Wextra -std=c++11 testClient.cpp -o testClient.exe
*/

int main()
{
    int sock; 
    struct sockaddr_in serv_addr; 


    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    { 
        std::cout << "Socket creation error" << std::endl;
        return -1; 
    } 
   
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(696); 
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        std::cout << "Connection Failed" << std::endl;
        return -1; 
    }

    // TODO

    return 0; 
}