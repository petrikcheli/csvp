#include "udp_client.h"

Udp_client::Udp_client(io_service& service)
    : _socket(service, _ep_client)
{
    this->start_client();
}

void Udp_client::start_client()
{
    bool send_flag = true;

    _socket.send_to(buffer((char*)&send_flag, sizeof(send_flag)), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_client::send_command(Game::Player &command)
{
    _socket.send_to(buffer((char*)&command, sizeof(command)), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_client::send_command(Game::BulletManager &command)
{
    _socket.send_to(buffer((char*)&command, sizeof(command)), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_client::recv_command(Game::Player &command)
{
    int bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
    memcpy(&command, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;
}

void Udp_client::recv_command(Game::BulletManager &command)
{
    int bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
    memcpy(&command, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;
}

void Udp_client::initialization_players(Game::Player &coord_player, Game::Player &coord_enemy)
{
    int bytes = 0;
    bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
    memcpy(&coord_player, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;


    bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
    memcpy(&coord_enemy, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;
}

void Udp_client::send_data_player(Game::Player &coord, Game::BulletManager &bul)
{
    _socket.send_to(buffer((char*)&coord, sizeof(coord)), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;

    _socket.send_to(buffer((char*)&bul, sizeof(bul)), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_client::recv_data_enemy(Game::Player &coord, Game::BulletManager &bul)
{
    int bytes = 0;
    bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
    memcpy(&coord, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;

    bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
    memcpy(&bul, _buff, bytes);
    if(_error_recv) std::cerr << "error - " << _error_recv;
}



void Udp_client::close_socket()
{
    _socket.close();
}
