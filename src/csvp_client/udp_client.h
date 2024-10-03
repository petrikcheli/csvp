#pragma once
#include <boost/asio.hpp>
#include "../game_logic/game.h"

using namespace boost::asio;

class Udp_client
{
    Udp_client();
public:

    Udp_client(io_service& service, std::string ip, unsigned short port);
    // Метод для инициализации клиента
    void start_client();

    // Метод для отправки команды серверу
    void send_coords(Game::Player& command);

    // Метод для отправки команды серверу
    void send_bullets(Game::BulletManager& command);

    // Метод для получения команды от сервера
    void recv_coords(Game::Player& command);

    // Метод для получения команды от сервера
    void recv_bullets(Game::BulletManager& command);

    void initialization_players(Game::Player& coord, Game::Player& bul);

    void send_data_player(Game::Player& coord, Game::BulletManager& bul);

    void recv_data_enemy(Game::Player& coord, Game::BulletManager& bul);

    void send_end_game();

    // Метод для закрытия сокета
    void close_socket();

private:
    char _buff[4096];

    ip::udp::endpoint _ep_server;//{ip::address::from_string("192.168.0.187"), 8000};
    //ip::udp::endpoint _ep_server{ip::address::from_string("127.0.0.1"), 8000};
    ip::udp::endpoint _ep_client{ip::udp::endpoint(ip::udp::v4(), 0)};

    ip::udp::socket _socket;

    boost::system::error_code _error_send;
    boost::system::error_code _error_recv;
};

