#include "server.h"
#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>

Server::Server() {}

Server::~Server(){
    close_all(); // Закрытие всех сокетов и освобождение ресурсов
}

int Server::start_server()
{
    socket_server = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_server == INVALID_SOCKET){
        std::cout << "Ошибка создания сокета" << std::endl;
        closesocket(socket_server); // Закрытие сокета при ошибке
        WSACleanup(); // Освобождение ресурсов Windows Sockets
        return -1;
    } else {
        std::cout << "Сокет успешно создан" << std::endl;
    }

    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(PORT_SERVER); // Указываем порт
    addr_server.sin_addr.s_addr = inet_addr(IP_SERVER); // Указываем IP-адрес

    if(bind(socket_server, (struct sockaddr *)&addr_server, sizeof(addr_server)) != 0){
        std::cout << "Ошибка привязки порта и IP к сокету" << std::endl;
        closesocket(socket_server); // Закрытие сокета при ошибке
        WSACleanup(); // Освобождение ресурсов Windows Sockets
        return -1;
    } else {
        std::cout << "Порт и IP успешно привязаны к сокету" << std::endl;
    }

    return 0;
}

int Server::listen_server()
{
    if(listen(socket_server, SOMAXCONN) != 0){
        std::cout << "Ошибка перехода в режим прослушивания" << std::endl;
        closesocket(socket_server); // Закрытие сокета при ошибке
        WSACleanup(); // Освобождение ресурсов Windows Sockets
        return -1;
    } else {
        std::cout << "Сервер в режиме прослушивания" << std::endl;
    }
    return 0;
}

int Server::accept_clients(SOCKET& socket_client, sockaddr_in& addr_client)
{
    ZeroMemory(&addr_client, sizeof(addr_client)); // Обнуление структуры адреса клиента

    int client_size = sizeof(addr_client);

    socket_client = accept(socket_server, (struct sockaddr *)&addr_client, &client_size);

    if(socket_client == INVALID_SOCKET){
        std::cout << "Ошибка подключения клиента" << std::endl;
        closesocket(socket_server); // Закрытие сервера при ошибке
        closesocket(socket_client); // Закрытие сокета клиента при ошибке
        WSACleanup(); // Освобождение ресурсов Windows Sockets
        return -1;
    }
    return 0;
}

int Server::send_client(SOCKET& socket_client, struct Game::Player& command)
{
    if(send(socket_client, (char *)&command, sizeof(command), 0) < 0){
        std::cout << "Ошибка отправки данных клиенту" << std::endl;
        return -1;
    }

    return 0;
}

int Server::recv_client(SOCKET& socket_client, struct Game::Player& command)
{
    if(recv(socket_client, (char *)&command, sizeof(command), 0) < 0){
        std::cout << "Ошибка получения данных от клиента" << std::endl;
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
