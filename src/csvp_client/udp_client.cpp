#include "udp_client.h"

Udp_client::Udp_client(io_service& service, std::string ip, unsigned short port)
    : _socket(service, _ep_client)
{
    _ep_server={ip::address::from_string(ip), port};
    this->start_client();
}

void Udp_client::start_client()
{
    bool send_flag = true;

    _socket.send_to(buffer((char*)&send_flag, sizeof(send_flag)), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_client::send_coords(Game::Player& command)
{
    //std::cerr << " send coords " << std::endl;
    size_t s = sizeof(command);
    _socket.send_to(buffer((char*)&command, s), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_client::send_bullets(Game::BulletManager& command)
{
    //std::cerr << " send size bullets " << std::endl;
    int size_bullets = command.bullets.size();
    _socket.send_to(buffer((char*)&size_bullets, sizeof(size_bullets)), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;

    if(size_bullets == 0) return;

    //прошлый код который отправлял все целиком
//    _socket.send_to(buffer((char*)&command.bullets, sizeof(command.bullets)), _ep_server, 0, _error_send);
//    if(_error_send)
//        std::cerr << "error - " << _error_send;

    //std::cerr << " send bullets "<<std::endl;
    //прошлый код который передава данные через цикл
    for(int i = 0; i < size_bullets; ++i){
        _socket.send_to(buffer((char*)&command.bullets[i], sizeof(command.bullets[i])), _ep_server, 0, _error_send);
        if(_error_send) std::cerr << "error - " << _error_send;
    }
}

void Udp_client::recv_coords(Game::Player &command)
{
    //std::cerr << " recv coords " << std::endl;
    size_t bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
    if(_error_recv) std::cerr << "error - " << _error_recv;
    memcpy(&command, _buff, bytes);
}

void Udp_client::recv_bullets(Game::BulletManager &command)
{
    //std::cerr << "recv size bullets" << std::endl;
    int size_bullets = 0;

    int bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
    memcpy(&size_bullets, _buff, sizeof(int));
    if(_error_recv) std::cerr << "error - " << _error_recv;

    if(size_bullets == 0) return;
    command.bullets.resize(size_bullets);

//    bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);

//    if(_error_recv)
//        std::cerr << "error - " << _error_recv;
//    memcpy(&command.bullets, _buff, bytes);
   // std::cerr << " recv bullets " << std::endl;
//прошлый код который передава данные через цикл
    for(int i = 0; i < size_bullets; ++i){
        //bytes = _socket.receive_from(buffer((char*)&command.bullets[i], sizeof(command.bullets[i])), _ep_client, 0, _error_recv);
        bytes = _socket.receive_from(buffer(_buff), _ep_client, 0, _error_recv);
        if(_error_recv) std::cerr << "error - " << _error_recv;
        memcpy(&command.bullets[i], _buff, bytes);
    }
}

void Udp_client:: initialization_players(Game::Player& coord_player, Game::Player& coord_enemy)
{
    this->recv_coords(coord_player);
    this->recv_coords(coord_enemy);
}

void Udp_client::send_data_player(Game::Player& coord, Game::BulletManager& bul)
{
    this->send_coords(coord);
    this->send_bullets(bul);
}

void Udp_client::recv_data_enemy(Game::Player& coord, Game::BulletManager& bul)
{

    this->recv_coords(coord);
    this->recv_bullets(bul);
}

void Udp_client::send_end_game()
{
    bool send_flag = true;
    _socket.send_to(buffer((char*)&send_flag, sizeof(send_flag)), _ep_server, 0, _error_send);
    if(_error_send) std::cerr << "error - " << _error_send;
}

void Udp_client::close_socket()
{
    _socket.close();
}
