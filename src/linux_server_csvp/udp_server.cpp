#include "udp_server.h"

Udp_server::Udp_server(io_service& service) : _socket(service, _ep_server)
{
    this->accept_clients();
}

void Udp_server::accept_clients()
{
    bool ready = false;

    int bytes = _socket.receive_from(buffer(_buff), client1, 0, _error_recv);
    memcpy(&ready, _buff, bytes);
    if(_error_recv || ready == false) this->accept_clients();

    //std::string message_wait = "Please wait second player";
    //_socket.send_to(buffer(message_wait), client1);

    ready = false;
    bytes = 0;
    while(true){
        bytes = _socket.receive_from(buffer(_buff), client2, 0, _error_recv);
        memcpy(&ready, _buff, bytes);
        if(ready) break;
    }
}

void Udp_server::send_coords(ip::udp::endpoint client, Game::Player &command)
{
    _socket.send_to(buffer((char*)&command, sizeof(command)), client, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_server::send_bullets(ip::udp::endpoint client, Game::BulletManager &command)
{
    int size_bullets = command.bullets.size();

    _socket.send_to(buffer((char*)&size_bullets, sizeof(int)), client, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;

    if(size_bullets == 0) return;

    for(int i = 0; i < size_bullets; ++i){
        _socket.send_to(buffer((char*)&command.bullets[i], sizeof(command.bullets[i])), client, 0, _error_send);
        if(_error_send) std::cerr << "error - " << _error_send;
    }
}

void Udp_server::recv_coords(ip::udp::endpoint client, Game::Player &command)
{
    int bytes = _socket.receive_from(buffer(_buff), client, 0, _error_recv);
    memcpy(&command, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;
}

void Udp_server::recv_bullets(ip::udp::endpoint client, Game::BulletManager &command)
{
    int size_bullets = 0;

    int bytes = _socket.receive_from(buffer(_buff), client, 0, _error_recv);
    if(_error_recv) std::cerr << "error - " << _error_recv;
    memcpy(&command, _buff, bytes);

    if(size_bullets == 0) return;

    for(int i = 0; i < size_bullets; ++i){
        int bytes = _socket.receive_from(buffer(_buff), client, 0, _error_recv);
        if(_error_recv) std::cerr << "error - " << _error_recv;
        memcpy(&command.bullets[i], _buff, bytes);
    }
}

void Udp_server::send_first_coordinate(Game::Player &player1, Game::Player &player2)
{
    this->send_coords(client1, player1);
    this->send_coords(client1, player2);

    this->send_coords(client2, player2);
    this->send_coords(client2, player1);
}

void Udp_server::recv_data_player(ip::udp::endpoint client, Game::Player &coord, Game::BulletManager &bul)
{
    this->recv_coords(client, coord);
    this->recv_bullets(client, bul);
}

void Udp_server::send_data_player(ip::udp::endpoint client, Game::Player &coord, Game::BulletManager &bul)
{
    this->send_coords(client, coord);
    this->send_bullets(client, bul);
}

void Udp_server::close_all()
{
    _socket.close();
}

