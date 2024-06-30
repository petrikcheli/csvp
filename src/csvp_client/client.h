#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
//#include <ws2tcpip.h>
#include <stdio.h>
#include <vector>
#include "../game_logic/game.h"

//#pragma comment(lib, "Ws2_32.lib")

class Client
{
    // Порт и IP-адрес сервера
    int PORT_SERVER = 8000;
    const char* IP_SERVER = "192.168.0.4";

    // Сокет и структура для адреса сервера
    SOCKET socket_server;
    sockaddr_in addr_server;

public:
    // Структура команды, можно расширить при необходимости
    struct Command{
        int command_type = 0;
    };

public:
    // Конструктор
    Client();

    // Деструктор
    ~Client();

    // Метод для инициализации клиента
    int start_client();

    // Метод для подключения к серверу
    int connect_to_server();

    // Метод для отправки команды серверу
    int send_command(struct Game::Player& command);

    // Метод для получения команды от сервера
    int recv_command(struct Game::Player& command);

    // Метод для закрытия сокета
    void close_socket();
};

#endif // CLIENT_H
