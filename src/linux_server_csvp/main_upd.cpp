#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "udp_server.h"
#include <windows.h>

using namespace std;
using namespace boost::asio;

bool g_game_is_active = true;

int main(){
    io_service service;

    setlocale(LC_ALL, "rus");



    //когда игра прекратится server снова начнет ждать новых клиентов
    start:
    //ip::udp::endpoint client1;
    //ip::udp::endpoint client2;

    Udp_server* server = new Udp_server(service);

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

    server->send_first_coordinate(server->client1, server->client2, data_player1, data_player2);

    while(g_game_is_active){
        //server->recv_data_player(server->client1, data_player1, bullets_player1);
        //server->recv_data_player(server->client2, data_player2, bullets_player2);
        server->recv_coords(data_player1, data_player2, bullets_player1, bullets_player2);
        server->recv_coords(data_player1, data_player2, bullets_player1, bullets_player2);
        server->recv_coords(data_player1, data_player2, bullets_player1, bullets_player2);
        server->recv_coords(data_player1, data_player2, bullets_player1, bullets_player2);

        server->send_data_player(server->client1, data_player2, bullets_player2);
        server->send_data_player(server->client2, data_player1, bullets_player1);
    }

    service.run();

    goto start;

    //delete server;

    return 0;
}
