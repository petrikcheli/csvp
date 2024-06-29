#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

//#pragma comment(lib, "Ws2_32.lib")



class Server
{

    const char* IP_SERVER = "192.168.0.4";
    const int PORT_SERVER = 8000;
    sockaddr_in addr_server;
    SOCKET socket_server;



    sockaddr_in addr_client;
    SOCKET socket_client;

public:
    struct Command{
        int command_type = 0;
    };

public:
    Server();
    ~Server();

    int start_server();
    int listen_server();
    int accpet_clients();
    int send_client(struct Command& command);
    int recv_client(struct Command& command);

    void close_all();
};

#endif // SERVER_H
