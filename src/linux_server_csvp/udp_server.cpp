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
    //if(_error_recv || ready == false) this->accept_clients(client1, client2);

    //std::string message_wait = "Please wait second player";
    //_socket.send_to(buffer(message_wait), client1);

    ready = false;
    bytes = _socket.receive_from(buffer(_buff), client2, 0, _error_recv);
    memcpy(&ready, _buff, bytes);
}

void Udp_server::send_coords(ip::udp::endpoint& client, Game::Player& command)
{
    _socket.send_to(buffer((char*)&command, sizeof(command)), client, 0, _error_send);

    //client.send_to(buffer((char*)&command, sizeof(command)), client.);
    if(_error_send) std::cerr << " error(31) - " << _error_send;
    std::cerr << " send coords " << std::endl;
}

void Udp_server::send_bullets(ip::udp::endpoint& client, Game::BulletManager& command)
{
    int size_bullets = command.bullets.size();

    _socket.send_to(buffer((char*)&size_bullets, sizeof(size_bullets)), client, 0, _error_send);
    //client.send(buffer((char*)&size_bullets, sizeof(size_bullets)));
    if(_error_send) std::cerr << " error(39) - " << _error_send;
    std::cerr << " send size bullets " << std::endl;
    if(size_bullets == 0) return;

    _socket.send_to(buffer((char*)&command.bullets, sizeof(command.bullets)), client, 0, _error_send);
    //client.send(buffer((char*)&command.bullets, sizeof(command.bullets)));
    if(_error_send)
        std::cerr << " error(45) - " << _error_send;
    std::cerr << " send_bullets ";
    //прошлый код который передава данные через цикл
//    for(int i = 0; i < size_bullets; ++i){
//        _socket.send_to(buffer((char*)&command.bullets[i], sizeof(command.bullets[i])), client, 0, _error_send);
//        if(_error_send)
//            std::cerr << " error(45) - " << _error_send;
//    }
}

void Udp_server::recv_coords(Game::Player& coord1, Game::Player& coord2,
                             Game::BulletManager &bul1, Game::BulletManager &bul2)
{
    int size_bullets;
    size_t bytes = _socket.receive_from(buffer(_buff), _ep_recv, 0, _error_recv);
    if(_error_recv) std::cerr << " error(53) - " << _error_recv;

    if(_ep_recv == client1){
        if(bytes > 4)
            memcpy(&coord1, _buff, bytes);
        else {
            memcpy(&size_bullets, _buff, bytes);
            std::cerr << " recv size bullets " << std::endl;

            if(size_bullets == 0) return;

            bul1.bullets.resize(size_bullets);
            bytes = _socket.receive_from(buffer(_buff), _ep_recv, 0, _error_recv);
            if(_error_recv) std::cerr << " error(68) - " << _error_recv;
            memcpy(&bul1.bullets, _buff, bytes);
            std::cerr << " recv bullets " << std::endl;
        }
    } else {
        if(bytes > 4)
            memcpy(&coord2, _buff, bytes);
        else{
            memcpy(&size_bullets, _buff, bytes);
                    std::cerr << " recv size bullets " << std::endl;

                    if(size_bullets == 0) return;

                    bul2.bullets.resize(size_bullets);
                    bytes = _socket.receive_from(buffer(_buff), _ep_recv, 0, _error_recv);
                    if(_error_recv) std::cerr << " error(68) - " << _error_recv;
                    memcpy(&bul2.bullets, _buff, bytes);
                    std::cerr << " recv bullets " << std::endl;
        }
    }



    std::cerr << " recv coords " << std::endl;
}

void Udp_server::recv_bullets(ip::udp::endpoint& client, Game::BulletManager &command)
{
    int size_bullets;
    size_t bytes = _socket.receive_from(buffer(_buff), client, 0, _error_recv);
    //size_t bytes = client.receive(buffer(_buff));
    if(bytes > 4) return;

    if(_error_recv) std::cerr << " error(61) - " << _error_recv;
    memcpy(&size_bullets, _buff, bytes);
    std::cerr << " recv size bullets " << std::endl;

    if(size_bullets == 0) return;

    command.bullets.resize(size_bullets);
    bytes = _socket.receive_from(buffer(_buff), client, 0, _error_recv);
    //bytes = client.receive(buffer(_buff));
    if(_error_recv) std::cerr << " error(68) - " << _error_recv;
    memcpy(&command.bullets, _buff, bytes);
    std::cerr << " recv bullets " << std::endl;
}

void Udp_server::send_first_coordinate(ip::udp::endpoint& client_1, ip::udp::endpoint& client_2,
                                       Game::Player &player1, Game::Player &player2)
{
    this->send_coords(client_1, player1);
    this->send_coords(client_1, player2);

    this->send_coords(client_2, player2);
    this->send_coords(client_2, player1);
}

void Udp_server::recv_data_player(ip::udp::endpoint& client, Game::Player& coord, Game::BulletManager& bul)
{
    //this->recv_coords(client, coord);
    this->recv_bullets(client, bul);
}

void Udp_server::send_data_player(ip::udp::endpoint& client, Game::Player &coord, Game::BulletManager &bul)
{
    this->send_coords(client, coord);
    this->send_bullets(client, bul);
}

void Udp_server::close_all()
{
    _socket.close();
}

