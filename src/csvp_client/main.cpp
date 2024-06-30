#include <iostream>
#include "client.h"
#include <windows.h>
//#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    setlocale(LC_ALL, "Rus");

    WSADATA wsaData;

    int result;

    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0){
        cout << "WSA failed" << endl;
        system("pause");
    }

    Client* client = new Client();
    Client::Command command;

    if(client->start_client() < 0){
        delete client;
        exit(1);
    }


    if(client->connect_to_server()< 0){
        delete client;
        exit(1);
    }

    while(true){

        std::cout << "Eneter the command" << std::endl;
        std::cin >> command.command_type;

        if(client->send_command(command) < 0){
            delete client;
            return -1;
        }

        if(command.command_type == 2){
            return 0;
        }
    }

    delete client;

    return 0;
}
