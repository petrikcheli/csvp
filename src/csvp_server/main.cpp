#include <iostream>
#include "server.h"

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

using namespace std;

int main()
{
    WSADATA wsaData;

    int result;

    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0){
        cout << "WSA failed" << endl;
    }

    Server* server = new Server();

    Server::Command command;

    if(server->start_server() < 0){
        delete server;
        return -1;
    }

    if(server->listen_server() < 0){
        delete server;
        return -1;
    }



    while(true){

        if(server->accpet_clients()< 0){
            delete server;
            return -1;
        }

        if(server->recv_client(command) < 0) {
            delete server;
            return -1;
        }
        if(command.command_type != 2) {
            std::cout << "Комманда - " << command.command_type << std::endl;
        } else{
             break;
        }
    }

    delete server;

    return 0;
}
