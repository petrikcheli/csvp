#include <iostream>
#include "server.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include "../game_logic/game.h"

using namespace std;

// Функция для обработки взаимодействия клиента и сервера
void work_client(Server* server, SOCKET socket_client, SOCKET socket_client2, Game::Player* data_send, Game::Player* data_recv){

    while(true){
        // Отправка данных от одного клиента другому
        if(server->send_client(socket_client2, *data_recv) < 0){
            delete server;
            system("pause");
        }

        // Получение данных от одного клиента
        if(server->recv_client(socket_client, *data_send) < 0) {
            delete server;
            system("pause");
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    WSADATA wsaData; // Структура для хранения информации о реализации Windows Sockets
    int result;

    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0){
        cout << "Ошибка инициализации WSA" << endl;
    }

    Server* server = new Server();

    Game::Map map; // Создание карты игры

    Game::Player data_player1; // Данные для первого игрока
    Game::Player data_player2; // Данные для второго игрока

    // Инициализация позиций игроков на карте
    data_player1.posX = map.WIDTH / 2;
    data_player1.posY = 1;

    data_player2.posX = map.WIDTH / 2;
    data_player2.posY = map.HEIGHT - 2;

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

    // Передача начальных позиций игрокам
    if (server->send_client(server->socket_client1, data_player1) < 0) {
        delete server;
        return -1;
    }

    if (server->send_client(server->socket_client2, data_player2) < 0) {
        delete server;
        return -1;
    }

    while(true){
        std::thread client1(work_client, server, server->socket_client1, server->socket_client2, &data_player1, &data_player2);
        client1.detach(); // Отсоединяем поток для работы в фоне

        work_client(server, server->socket_client2, server->socket_client1, &data_player2, &data_player1);
    }

    delete server;

    return 0;
}
