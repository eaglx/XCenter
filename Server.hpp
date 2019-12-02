
#include <unistd.h>
#include <sys/socket.h> 
#include <netinet/in.h>

struct MESSAGE_INFO
{
    int flag;
    int posX;
    int posY;
    char key;
};

class CServer{
    private:
        int port;
        int backlogQueueSize;
        int server_fd;
        int opt;
        struct sockaddr_in address;

        void serialize_msg(MESSAGE_INFO*, char*);
        void deserialize_msg(char*, MESSAGE_INFO*);
    public:
        CServer();
        CServer(int, int);
        ~CServer();
        int setup();
        void loop();
};