#include "udp_server.h"

Udp_server::Udp_server(io_service& service) : _socket(service, _ep_server)
{
    accept_clients();
}

void Udp_server::accept_clients()
{
    bool ready = false;

    int bytes = _socket.receive_from(buffer(_buff), client1, 0, _error_recv);
    memcpy(&ready, _buff, bytes);
    if(_error_recv || ready == false) this->accept_clients();

    std::string message_wait = "Please wait second player";
    _socket.send_to(buffer(message_wait), client1);

    ready = false;
    bytes = 0;
    while(true){
        bytes = _socket.receive_from(buffer(_buff), client2, 0, _error_recv);
        memcpy(&ready, _buff, bytes);
        if(!_error_recv && ready == true) break;
    }
}

void Udp_server::send_client(ip::udp::endpoint client, Game::Player &command)
{
    _socket.send_to(buffer((char*)&command, sizeof(command)), client, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_server::send_client(ip::udp::endpoint client, Game::BulletManager &command)
{
    _socket.send_to(buffer((char*)&command, sizeof(command)), client, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_server::recv_client(ip::udp::endpoint client, Game::Player &command)
{
    int bytes = _socket.receive_from(buffer(_buff), client, 0, _error_recv);
    memcpy(&command, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;
}

void Udp_server::recv_client(ip::udp::endpoint client, Game::BulletManager &command)
{
    int bytes = _socket.receive_from(buffer(_buff), client, 0, _error_recv);
    memcpy(&command, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;
}

void Udp_server::send_first_coordinate(Game::Player &player1, Game::Player &player2)
{
    this->send_client(client1, player1);
    this->send_client(client1, player2);

    this->send_client(client2, player2);
    this->send_client(client2, player1);
}

void Udp_server::recv_data_player(ip::udp::endpoint client, Game::Player &coord, Game::BulletManager &bul)
{
    this->recv_client(client, coord);
    this->recv_client(client, bul);
}

void Udp_server::send_data_player(ip::udp::endpoint client, Game::Player &coord, Game::BulletManager &bul)
{
    this->send_client(client, coord);
    this->send_client(client, bul);
}

void Udp_server::close_all()
{
    _socket.close();
}

