#include "server.h"

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

Server::Server()
{

}

Server::~Server(){
    close_all();
}

int Server::start_server()
{

    socket_server = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_server == INVALID_SOCKET){
        std::cout << "Failed to create socket" << std::endl;
        closesocket(socket_server);
        WSACleanup();
        return -1;
    } else {
        std::cout << "Managed to create socket" << std::endl;
    }

    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(PORT_SERVER);
    addr_server.sin_addr.s_addr = inet_addr(IP_SERVER);

    if(bind(socket_server, (struct sockaddr *)&addr_server, sizeof(addr_server)) != 0){
        std::cout << "Failed to associate port and ip with socket" << std::endl;
        closesocket(socket_server);
        WSACleanup();
        return -1;
    } else {
        std::cout << "port and ip associat with socket" << std::endl;
    }

    return 0;
}

int Server::listen_server()
{
    if(listen(socket_server, SOMAXCONN) != 0){
        std::cout << "Failed to put the port into listening mode" << std::endl;
        closesocket(socket_server);
        WSACleanup();
        return -1;
    } else {
        std::cout << "Socket in listening mode" << std::endl;
    }
    return 0;
}

int Server::accept_clients(SOCKET& socket_client, sockaddr_in& addr_client)
{
    ZeroMemory(&addr_client, sizeof(addr_client));

    int client_size = sizeof(addr_client);

    socket_client = accept(socket_server, (struct sockaddr *)&addr_client, &client_size);

    if(socket_client == INVALID_SOCKET){
        std::cout << "Failed to connect client" << std::endl;
        closesocket(socket_server);
        closesocket(socket_client);
        WSACleanup();
        return -1;
    }
    return 0;
}

int Server::send_client(SOCKET& socket_client, struct Command& command)
{
    if(send(socket_client, (char *)&command, sizeof(command), 0) < 0){
        std::cout << "Failed to send message to client" << std::endl;
        return -1;
    }

    return 0;
}

int Server::recv_client(SOCKET& socket_client, struct Command& command)
{
    if(recv(socket_client, (char *)&command, sizeof(command), 0) < 0){
        std::cout << "Failed to receive message from client" << std::endl;
        return -1;
    }

    return 0;
}

void Server::close_all()
{
    shutdown(socket_server, 2);
    shutdown(socket_client1, 2);
    shutdown(socket_client2, 2);
    closesocket(socket_server);
    closesocket(socket_client1);
    closesocket(socket_client2);
    WSACleanup();
}

