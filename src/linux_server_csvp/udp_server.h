#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include "../game_logic/game.h"

using namespace boost::asio;

class Udp_server
{
    Udp_server();
public:

    Udp_server(io_service& service);

    void start_server();

    void accept_clients();
    void send_client(ip::udp::endpoint client, struct Game::Player& command);
    void send_client(ip::udp::endpoint client, struct Game::BulletManager& command);
    void recv_client(ip::udp::endpoint client, struct Game::Player& command);
    void recv_client(ip::udp::endpoint client, struct Game::BulletManager& command);

    void send_first_coordinate(Game::Player &player1, Game::Player &player2);

    void recv_data_player(ip::udp::endpoint client, Game::Player &coord,
                                                    Game::BulletManager& bul);

    void send_data_player(ip::udp::endpoint client, Game::Player &coord,
                                                    Game::BulletManager& bul);

    void close_all();

public:
    ip::udp::endpoint client1;
    ip::udp::endpoint client2;

private:
    //ip::udp::endpoint _ep_server{ip::address::from_string("217.144.103.236"), 8000};
    ip::udp::endpoint _ep_server{ip::address::from_string("127.0.0.1"), 8000};
    ip::udp::socket _socket;

    boost::system::error_code _error_recv;
    boost::system::error_code _error_send;

    char* _buff[1024];
};

