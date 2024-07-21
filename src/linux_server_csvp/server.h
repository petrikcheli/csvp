#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <string>
#include "../game_logic/game.h"

class Server
{
    int PORT_SERVER = 8000;
    const char* IP_SERVER = "217.144.103.236";

    sockaddr_in addr_server;
    int socket_server;

public:
    sockaddr_in addr_client1;
    int socket_client1;

    sockaddr_in addr_client2;
    int socket_client2;

    bool isRunning = true;
    struct Player{
        char playerIcon = 'O';
        int posX = 0;
        int posY = 0;
        bool isAlive = true;
    };
    struct Map{
        std::vector<std::string> gameMap = {
            "############################################################",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "#                                                          #",
            "############################################################"
        };
        const int WIDTH = 60;
        const int HEIGHT = 20;
    };
    struct Bullet{
        int posX;
        int posY;

        enum Direction { UP, DOWN, LEFT, RIGHT } direction;
    };

    struct BulletManager{
        std::vector<Bullet> bullets;
    };

    struct Size_Bullets{
        int size = 0;
    };

public:
    Server();
    ~Server();

    int start_server();
    int listen_server();
    int accept_clients(int& socket_client, sockaddr_in& addr_client);
    int send_client(int& socket_client, struct Game::Player& command);
    int send_client(int& socket_client, struct Game::BulletManager& command);
    int recv_client(int& socket_client, struct Game::Player& command);
    int recv_client(int& socket_client, struct Game::BulletManager& command);

    void close_all();
};

#endif // SERVER_H
