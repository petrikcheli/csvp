#include <iostream>
#include "server.h"
#include <sys/socket.h> // сокеты
#include <netinet/in.h> // константы для работы с портами и ip и структура
#include <arpa/inet.h> // ip address, его нужно чтобы передать в строке ip
#include <unistd.h> // закрыть порты
#include <thread>

using namespace std;

// главная функция работы с двумя клиентами
void work_client(Server* server, int socket_client1, int socket_client2,
                 Server::Player data_player1, Server::Player data_player2,
                 Server::BulletManager bullets_player1, Server::BulletManager bullets_player2){

    //эта строчка отработает только один раз, когда начнется игра
    //отправляем клиенту его начальные координаты
    if(server->send_client(socket_client1, data_player1) < 0){
        delete server;
        system("pause");
    }
    std::cerr << "player1 -> data1" << std::endl;

    if(server->send_client(socket_client2, data_player2) < 0){
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

    if(server->send_client(socket_client2, data_player1) < 0){
        delete server;
        system("pause");
    }
    std::cerr << "player1 -> data2" << std::endl;

    //в бесконечном цикле идет вся работа с клиентами
    //сначала он принимает координаты от одного клиента, а потом отравляет их другому клиенту
    while(true){
        if(server->recv_client(socket_client1, data_player1) < 0) {
            delete server;

            system("pause");
        }
        std::cerr << "player1 -> data1" << std::endl;

        if(server->recv_client(socket_client2, data_player2) < 0) {
            delete server;

            system("pause");
        }
        std::cerr << "player2 -> data2" << std::endl;

        if(server->recv_client(socket_client1, bullets_player1) < 0) {
            delete server;

            system("pause");
        }
        std::cerr << "player1 -> bullet1" << std::endl;

        if(server->recv_client(socket_client2, data_player2) < 0) {
            delete server;

            system("pause");
        }
        std::cerr << "player2 -> bullet2" << std::endl;

        if(server->send_client(socket_client2, data_player1) < 0){
            delete server;
            system("pause");
        }
        std::cerr << "player2 -> data1" << std::endl;

        if(server->send_client(socket_client1, data_player2) < 0){
            delete server;
            system("pause");
        }
        std::cerr << "player2 -> data1" << std::endl;

        if(server->send_client(socket_client2, bullets_player1) < 0){
            delete server;
            system("pause");
        }
        std::cerr << "player2 -> bullets1" << std::endl;

        if(server->send_client(socket_client1, bullets_player2) < 0){
            delete server;
            system("pause");
        }
        std::cerr << "player2 -> bullets2" << std::endl;
    }
}

int main()
{
    // устанавливаем русский язык
    setlocale(LC_ALL, "Russian");

    // создаем объект класса Server
    Server* server = new Server();

    // map, data_player1, data_player2
    //нужны для того чтобы отсылать/принимать
    Server::Map map;

    Server::Player data_player1;
    Server::Player data_player2;

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
    // std::thread client1(work_client, server, server->socket_client1, server->socket_client2, data_player1, data_player2);
    // client1.detach();

    // //создаем третий поток
    // std::thread client2(work_client, server, server->socket_client2, server->socket_client1, data_player2, data_player1);
    // client2.detach();

    //так как остался самый первый поток, то я его увожу в бесконечный цикл


    while(true){
        work_client(server, server->socket_client1, server->socket_client2, data_player1, data_player2);
    }

    delete server;

    return 0;
}

