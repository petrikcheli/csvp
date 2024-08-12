#pragma once
#include <iostream>
#include <boost/asio.hpp>
//#include <boost/bind.hpp>
#include "../game_logic/game.h"

using namespace boost::asio;

class Udp_server
{
    Udp_server();
public:

    Udp_server(io_service& service);

    void start_server();

    void accept_clients();
    void send_coords(ip::udp::endpoint& client, struct Game::Player& command);
    void send_bullets(ip::udp::endpoint& client, struct Game::BulletManager& command);
    int recv_coords(Game::Player& coord1, Game::Player& coord2,
                     Game::BulletManager &bul1, Game::BulletManager &bul2);
    void recv_bullets(ip::udp::endpoint& client, struct Game::BulletManager& command);

    void send_first_coordinate(ip::udp::endpoint& client_1, ip::udp::endpoint& client_2,
                               Game::Player &player1, Game::Player &player2);

    void recv_data_player(ip::udp::endpoint& client, Game::Player &coord,
                                                    Game::BulletManager& bul);

    void send_data_player(ip::udp::endpoint& client, Game::Player &coord,
                                                    Game::BulletManager& bul);

    void close_all();

public:
    ip::udp::endpoint client1;
    ip::udp::endpoint client2;
    bool game_is_active = true;

private:
    //ip::udp::endpoint _ep_server{ip::address::from_string("217.144.103.236"), 8000};
    //ip::udp::endpoint _ep_server{ip::address::from_string("127.0.0.1"), 8000};
    ip::udp::endpoint _ep_server{ip::address::from_string("192.168.0.187"), 8000};
    ip::udp::endpoint _ep_recv;
    ip::udp::socket _socket;

    boost::system::error_code _error_recv;
    boost::system::error_code _error_send;

    char _buff[4096];
    //char _buff_recv[4096];
};

