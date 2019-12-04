#include "Server.hpp"

#include <memory> // For unique_ptr
#include "Mouse.hpp"
/*
#include <signal.h>
#define SIGHUP  1   // Hangup the process 
#define SIGINT  2   // Interrupt the process 
#define SIGQUIT 3   // Quit the process
#define SIGILL  4   // Illegal instruction
#define SIGTRAP 5   // Trace trap
#define SIGABRT 6   // Abort
void signal_callback_handler(int signum);
*/

CServer::CServer()
{
    this->port = 696;
    this->backlogQueueSize = 3;
    opt = 1;
    endLoop = false;
    sockAddrSize = sizeof(struct sockaddr);
}

CServer::CServer(int port, int backlogQueueSize)
{
    this->port = port;
    this->backlogQueueSize = backlogQueueSize;
    opt = 1;
    endLoop = false;
    sockAddrSize = sizeof(struct sockaddr);
}

CServer::~CServer()
{

}

int CServer::setup()
{
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        return -301; 
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        return -302;
    }

    // server byte order
    address.sin_family = AF_INET;  
    // automatically be filled with current host's IP address
    address.sin_addr.s_addr = INADDR_ANY; 
    // convert short integer value for port must be converted into network byte order
    address.sin_port = htons( port );

    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) 
    { 
        return -303;
    }

    if (listen(server_fd, backlogQueueSize) < 0) 
    { 
        return -304;
    } 


}

int CServer::sendData(int socket, void *buffer, size_t length)
{
    char *ptr = (char*) buffer;
    int d;

    while (length > 0)
    {
        d = send(socket, ptr, length, 0);
        if (d < 0) return SEND_ERROR;
        else if(d == 0) return SEND_ZERO;
        ptr += d;
        length -= d;
    }
    return SEND_ALL_DATA;
}

int CServer::recvData(int socket, void *buffer, size_t length)
{
    char *ptr = (char*) buffer;
    int d;
    int iteration = 0;
    bool loopFinish = false;

    while (!loopFinish)
    {
        d = recv(socket, ptr, length, 0);
        if (d == -1) return RECIVE_ERROR;
        else if(d == 0)
        {
            if(iteration == 0) return RECIVE_ZERO;
            else loopFinish = true;
        }
        ptr += d;
        length -= d;
        ++iteration;
        if(length <= 0) loopFinish = true;
    }
    return d;
}

void CServer::workWithClient(int clifd)
{
    char buffer[PACKETSIZE];
    MESSAGE_INFO msgInfo;
    int info;

    std::unique_ptr<Mouse> m(new Mouse());

    if(!m->initMouseModule()) {
        std::cout << "ERROR: FAILED TO INIT Mouse MODULE!" << std::endl;
        return;
    }

    msgInfo.flag = FLAG_CONFIRMCONN;
    serialize_msg(&msgInfo, buffer);
    info = sendData(clifd, buffer, sizeof(buffer)/sizeof(buffer[0]));
    if(info != SEND_ALL_DATA)
    {
        std::cout << "FAILED FLAG_CONFIRMCONN" <<std::endl;
        close(clifd);
        return;
    }
    else
    {
        while(true)
        {
            info = recvData(clifd, buffer, sizeof(buffer)/sizeof(buffer[0]));
            if(errno == ECONNRESET) continue; // Connection reset
            else if(errno == EPIPE) continue; // Broken pipe
            else if(errno == EWOULDBLOCK) // Resource temporarily unavailable
            {
                std::cout << "FAILED EWOULDBLOCK" <<std::endl;
                close(clifd);
                return;
            }

            if(info == RECIVE_ERROR)
            {
                std::cout << "FAILED RECIVE_ERROR" <<std::endl;
                close(clifd);
                return;
            }
            else if(info == RECIVE_ZERO)
            {
                std::cout << "FAILED RECIVE_ZERO" <<std::endl;
                close(clifd);
                return;
            }
            else
            {
                deserialize_msg(buffer, &msgInfo);
                if(msgInfo.flag == FLAG_CONFIRMCONN)
                {
                    msgInfo.flag = FLAG_CONFIRMCONN;
                    serialize_msg(&msgInfo, buffer);
                    sendData(clifd, buffer, sizeof(buffer)/sizeof(buffer[0]));
                }
                else if(msgInfo.flag == FLAG_DISCONN)
                {
                    close(clifd);
                    return;
                }
                else if(msgInfo.flag == FLAG_MOUSE) // Possible vulnerability!
                {
                    m->updateCursorPosition(msgInfo.posX, msgInfo.posY);
                }
                else if(msgInfo.flag == FLAG_KEYBOARD) // TODO
                {
                    ;
                }
                else
                {
                    std::cout << "UNKNOW FLAG" <<std::endl;
                }
                
            }
            
        }
    }
}

void CServer::loop()
{
    int client_fd;

    while(!endLoop)
    {
        client_fd = accept(server_fd, (struct sockaddr *) &clientAddr, &sockAddrSize);
        if(client_fd > 0)
        {
            workWithClient(client_fd);
        }
        else
        {
            std::cout << "accept() FAILED" << std::endl;
        }
        
    }
    return;
}

void CServer::serialize_msg(MESSAGE_INFO *msgPacket, char *data) // Possible vulnerability!
{
    int *q = (int *)data;
	*q = msgPacket->flag; q++;
	*q = msgPacket->posX; q++;
    *q = msgPacket->posY; q++;
	char *p = (char *)q;
    *p = msgPacket->key; p++;
}

void CServer::deserialize_msg(char *data, MESSAGE_INFO *msgPacket) // Possible vulnerability!
{
    int *q = (int *)data;
	msgPacket->flag = *q; q++;
	msgPacket->posX = *q; q++;
    msgPacket->posY = *q; q++;
	char *p = (char *)q;
    msgPacket->key = *p; p++;
}