
#include <unistd.h>
#include <sys/socket.h> 
#include <netinet/in.h>

#include <iostream>
#include <errno.h>

#define SEND_ALL_DATA 1
#define SEND_ZERO 0
#define SEND_ERROR -1
#define RECIVE_ZERO 0
#define RECIVE_ERROR -1

#define FLAG_CONFIRMCONN 11
#define FLAG_DISCONN 22
#define FLAG_MOUSE 33
#define FLAG_KEYBOARD 44

struct MESSAGE_INFO
{
    int flag;
    int posX;
    int posY;
    char key;
};

#define PACKETSIZE sizeof(MESSAGE_INFO)

class CServer{
    private:
        int port;
        int backlogQueueSize;
        int server_fd;
        int opt;
        bool endLoop;
        struct sockaddr_in address, clientAddr;
        socklen_t sockAddrSize;

        void serialize_msg(MESSAGE_INFO*, char*);
        void deserialize_msg(char*, MESSAGE_INFO*);
        int sendData(int, void*, size_t);
        int recvData(int, void*, size_t);
        void workWithClient(int);

    public:
        CServer();
        CServer(int, int);
        ~CServer();
        int setup();
        void loop();
};