#include "Server.hpp"

CServer::CServer()
{
    this->port = 696;
    this->backlogQueueSize = 5;
    opt = 1;
}

CServer::CServer(int port, int backlogQueueSize)
{
    this->port = port;
    this->backlogQueueSize = backlogQueueSize;
    opt = 1;
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

void CServer::loop() // ***************** TODO
{
    // while()
    // {

    // }
    return;
}

void CServer::serialize_msg(MESSAGE_INFO *msgPacket, char *data)
{
    int *q = (int *)data;
	*q = msgPacket->flag; q++;
	*q = msgPacket->posX; q++;
	char *p = (char *)q;
    *p = msgPacket->key; p++;
}

void CServer::deserialize_msg(char *data, MESSAGE_INFO *msgPacket)
{
    int *q = (int *)data;
	msgPacket->flag = *q; q++;
	msgPacket->posX = *q; q++;
	char *p = (char *)q;
    msgPacket->key = *p; p++;
}