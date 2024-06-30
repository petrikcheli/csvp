#include <iostream>
#include "client.h"
#include <windows.h>
#include "game.h"
//#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    Game game;
    Game::Player player;
    Game::Map map;
    Game::Player enemy;

    // ????????????? ??????? ?????? ? ?????

    setlocale(LC_ALL, "Rus");

    WSADATA wsaData;

    int result;

    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0){
        cout << "WSA failed" << endl;
        system("pause");
    }

    Client* client = new Client();
    Client::Command command;

    if(client->start_client() < 0){
        delete client;
        exit(1);
    }


    if(client->connect_to_server()< 0){
        delete client;
        exit(1);
    }

    while(game.isRunning){

        if(client->recv_command(enemy) < 0){
            delete client;
            system("pause");
            return -1;
        }

        if(client->send_command(player) < 0){
            delete client;
            system("pause");
            return -1;

        }

        int oldX = player.posX;
        int oldY = player.posY;

        int oldEnemyX = enemy.posX;
        int oldEnemyY = enemy.posY;

        game.handleInput(player, map);

        // ?????????? ????? ? ???????
        map.setCursor(0, 0);
        map.updateMap(player, oldX, oldY);
        map.updateMap(enemy, oldEnemyX, oldEnemyY);

        map.display();
        Sleep(100);

    }

    delete client;

    return 0;
}
