﻿#include <iostream>
#include "client.h"
#include <windows.h>
#include <thread>
#include "../game_logic/game.h"
#include "../game_logic/screensaver.h"
//#pragma comment(lib, "ws2_32.lib")

using namespace std;

int initialization_players(Client* client, Game::Player& player, Game::Player& enemy){
    //принимаем первоначальные координаты player
    if(client->recv_command(player) < 0){
        delete client;
        return -1;
    }

    //принимаем первоначальные координаты противника
    if(client->recv_command(enemy) < 0){
        delete client;
        return -1;
    }

    return 0;
}

int send_player_data(Client* client, Game::Player& player, Game::BulletManager& playerBullet){
    //отправляем свои координаты, чтобы сервер их передал противнику
    if(client->send_command(player) < 0){
        delete client;
        return -1;

    }
    // отправляем массив своих пуль
    if(client->send_command(playerBullet) < 0){
        delete client;
        return -1;

    }
    return 0;
}

int recv_enemy_data(Client* client, Game::Player& enemy, Game::BulletManager& enemyBullet){

    // после того как мы запомнили прошлые координаты, можно принять новые
    if(client->recv_command(enemy) < 0){
        delete client;
        return -1;
    }

    // принимаем массив пуль от противника
    if(client->recv_command(enemyBullet) < 0){
        delete client;
        return -1;
    }

    return 0;
}

void update_map(Game& game, Game::Map& map, Game::Player& player, Game::Player& enemy,
                Game::BulletManager& playerBullet, Game::BulletManager& enemyBullet,
                int oldX, int oldY, int oldEnemyX, int oldEnemyY){
    game.updateBullets(map, playerBullet);
    game.updateBullets(map, enemyBullet);
    map.updateMap(player, oldX, oldY);
    map.updateMap(enemy, oldEnemyX, oldEnemyY);

    game.endGame(enemy, playerBullet);
    game.endGame(player, enemyBullet);
}

int main()
{
    // Создаем объекты игры, игрока, карты и противника
    Game game;
    Game::Player player;
    Game::Map map;
    Game::Player enemy;
    Game::BulletManager playerBullet;
    Game::BulletManager enemyBullet;

    Rocket rocket;

    // Устанавливаем локализацию на русский язык для вывода в консоль
    setlocale(LC_ALL, "Rus");

    WSADATA wsaData; // Структура для хранения информации о реализации Windows Sockets

    int result;

    // Инициализация библиотеки Windows Sockets
    result = WSAStartup(MAKEWORD(2,2), &wsaData);
    if(result != 0){
        cout << "Ошибка инициализации WSA" << endl;
        system("pause");
    }

    // Создаем объект клиента для сетевого взаимодействия
    Client* client = new Client();
    Client::Command command;

    //создаем сокет и связываем его с портом и ip
    if(client->start_client() < 0){
        delete client;
        exit(1);
    }

    //подключаемся к серверу
    if(client->connect_to_server()< 0){
        delete client;
        exit(1);
    }

    if(initialization_players(client, player, enemy) < 0){
        system("pause");
        return -1;
    }

    // rocket.printScreenSaver();

    // Главный игровой цикл
    while(game.isRunning){
        
        // Принимаем данные на сервер
        if(send_player_data(client, player, playerBullet)){
            system("pause");
            return -1;
        }

        // Сохраняем старые координаты игрока и противника для последующего обновления карты
        int oldX = player.posX;
        int oldY = player.posY;

        int oldEnemyX = enemy.posX;
        int oldEnemyY = enemy.posY;

        // Обрабатываем ввод игрока и обновляем состояние игры
        game.handleInput(player, map, playerBullet);

        // Перемещаем курсор в начало консоли для перерисовки карты
        map.setCursor(0, 0);

        // Принимаем данные на сервер
        if(recv_enemy_data(client, enemy, enemyBullet) < 0){
            system("pause");
            return -1;
        }

        // Обновляем карту с новыми позициями игрока и противника
        update_map(game, map, player,
                   enemy, playerBullet, enemyBullet,
                   oldX, oldY, oldEnemyX, oldEnemyY);

        // Отображаем карту на экране
        map.display();

        // Задержка для плавности анимации
        Sleep(100);
    }

    // Освобождаем память и закрываем соединение
    delete client;

    return 0;
}
