#include <iostream>
#include "server.h"

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <thread>

using namespace std;


void work_client(Server* server, SOCKET socket_client, SOCKET socket_client2, Server::Player command){
    while(true){

        if(server->recv_client(socket_client, command) < 0) {
            delete server;
            system("pause");
        }

        if(server->send_client(socket_client2, command) < 0){
            delete server;
            system("pause");
        }


//        if(command.command_type != 2) {
//            std::cout << "Command - " << command.command_type << std::endl;
//        } else{
//            system("pause");
//        }
    }
}

int main()
{

    setlocale(LC_ALL, "Russian");

    WSADATA wsaData;

    int result;

    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0){
        cout << "WSA failed" << endl;
    }

    Server* server = new Server();

    Server::Player data_player1;
    Server::Player data_player2;

    if(server->start_server() < 0){
        delete server;
        return -1;
    }

    if(server->listen_server() < 0){
        delete server;
        return -1;
    }

    if(server->accept_clients(server->socket_client1, server->addr_client1) < 0){
        delete server;
        system("pause");
        return -1;
    }

    if(server->accept_clients(server->socket_client2, server->addr_client2) < 0){
        delete server;
        system("pause");
        return -1;
    }

    while(true){
        std::thread client1(work_client, server, server->socket_client1, server->socket_client2, data_player1);
        client1.detach();
        work_client(server, server->socket_client2, server->socket_client1, data_player2);
    }

    delete server;

    return 0;
}

