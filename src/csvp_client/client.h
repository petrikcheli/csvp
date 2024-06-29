#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
//#include <ws2tcpip.h>
#include <stdio.h>
#include <vector>

//#pragma comment(lib, "Ws2_32.lib")

class Client
{

    int PORT_SERVER = 8000;
    const char* IP_SERVER = "192.168.0.4";
    SOCKET socket_server;
    sockaddr_in addr_server;

public:
    struct Command{
        int command_type = 0;
    };

public:
    Client();
    ~Client();
    int start_client();
    int connect_to_server();
    int send_command(struct Command& command);
    int recv_command(struct Command& command);

    void close_socket();
};

#endif // CLIENT_H
