#include <iostream>
#include "server.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <vector>
#include <thread>
#include "../game_logic/game.h"

using namespace std;

// главная функция работы с двумя клиентами
void work_client(Server* server, SOCKET socket_client1, SOCKET socket_client2,
                 Game::Player data_player1, Game::Player data_player2,
                 Game::BulletManager bullets_player1, Game::BulletManager bullets_player2){

    //эта строчка отработает только один раз, когда начнется игра
    //отправляем клиенту его начальные координаты 
    if(server->send_client(socket_client1, data_player1) < 0){
        delete server;
        system("pause");
    }
    std::cerr << "player1 -> data1" << std::endl;

    //эта строчка отработает только один раз, когда начнется игра
    //отправляем клиенту координаты противника
    if(server->send_client(socket_client1, data_player2) < 0){
        delete server;
        system("pause");
    }
    std::cerr << "player1 -> data2" << std::endl;

    //в бесконечном цикле идет вся работа с клиентами
    //сначала он принимает координаты от одного клиента, а потом отравляет их другому клиенту
    while(true){
        //принимаем координаты клиента1
        if(server->recv_client(socket_client1, data_player1) < 0) {
            delete server;

            system("pause");
        }
        std::cerr << "player1 -> data1" << std::endl;

        //принимаем массив пуль клиента1
        if(server->recv_client(socket_client1, bullets_player1) < 0) {
            delete server;

            system("pause");
        }
        std::cerr << "bullets_player1 -> data1" << std::endl;

        //отправляем координаты клиента1 клиенту2
        if(server->send_client(socket_client2, data_player1) < 0){
            delete server;
            system("pause");
        }
        std::cerr << "player2 -> data1" << std::endl;

        //отправляем массив пуль клиента1 клиенту2
        if(server->send_client(socket_client2, bullets_player1) < 0){
            delete server;
            system("pause");
        }
        std::cerr << "bullet_player1 -> player2" << std::endl;
    }
}

int main()
{
    // устанавливаем русский язык
    setlocale(LC_ALL, "Russian");


    WSADATA wsaData; // Структура для хранения информации о реализации Windows Sockets

    //проверяем правильность подключения библиотеки wsa_32.lib (подробности в cmake)
    int result;
    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0){
        cout << "WSA failed" << endl;
    }

    // создаем объект класса Server
    Server* server = new Server();

    // map, data_player1, data_player2
    //нужны для того чтобы отсылать/принимать  
    Game::Map map;

    Game::Player data_player1;
    Game::Player data_player2;
    Game::BulletManager bullets_player1;
    Game::BulletManager bullets_player2;

    // сервер самостоятельно определяет, кто будет сверху, а кто будет снизу
    // соответсвенно тут проходит инциализация начальных координат
    data_player1.posX = map.WIDTH / 2;
    data_player1.posY = 1;

    data_player2.posX = map.WIDTH / 2;
    data_player2.posY = map.HEIGHT - 2;

    //создаем сокет и связываем его с портом и ip
    if(server->start_server() < 0){
        delete server;
        return -1;
    }

    // ставим сокет в режим прослушивания
    if(server->listen_server() < 0){
        delete server;
        return -1;
    }

    //принимаем первого клиента
    if(server->accept_clients(server->socket_client1, server->addr_client1) < 0){
        delete server;
        system("pause");
        return -1;
    }

    //принимаем второго клиента
    if(server->accept_clients(server->socket_client2, server->addr_client2) < 0){
        delete server;
        system("pause");
        return -1;
    }

    //создаем второй поток
    std::thread client1(work_client, server, server->socket_client1, server->socket_client2, data_player1, data_player2,
                        bullets_player1, bullets_player2);
    client1.detach();

    //создаем третий поток
    std::thread client2(work_client, server, server->socket_client2, server->socket_client1, data_player2, data_player1,
                        bullets_player1, bullets_player2);
    client2.detach();

    //так как остался самый первый поток, то я его увожу в бесконечный цикл
    while(true){}

    delete server;

    return 0;
}

