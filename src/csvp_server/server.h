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


public:
    sockaddr_in addr_client1;
    SOCKET socket_client1;

    sockaddr_in addr_client2;
    SOCKET socket_client2;

public:
    struct Command{
        int command_type = 0;
    };
    struct Player{
        char playerIcon = 'O';
        int posX = 0;
        int posY = 0;
        bool isAlive = true;
    };

public:
    Server();
    ~Server();

    int start_server();
    int listen_server();
    int accept_clients(SOCKET& socket_client, sockaddr_in& addr_client);
    int send_client(SOCKET& socket_client, struct Player& command);
    int recv_client(SOCKET& socket_client, struct Player& command);

    void close_all();
};

#endif // SERVER_H
