#include <iostream>
#include "client.h"
#include <windows.h>
#include "../game_logic/game.h"
//#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    // Создаем объекты игры, игрока, карты и противника
    Game game;
    Game::Player player;
    Game::Map map;
    Game::Player enemy;

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
        system("pause");
        exit(1);
    }

    //принимаем первоначальные координаты player
    if(client->recv_command(player) < 0){
        delete client;
        system("pause");
        return -1;
    }

    //принимаем первоначальные координаты противника
    if(client->recv_command(enemy) < 0){
        delete client;
        system("pause");
        return -1;
    }

    // Главный игровой цикл
    while(game.isRunning){
        
        //отправляем свои координаты, чтобы сервер их передал противнику
        if(client->send_command(player) < 0){
            delete client;
            system("pause");
            return -1;

        }

        // Сохраняем старые координаты игрока и противника для последующего обновления карты
        int oldX = player.posX;
        int oldY = player.posY;

        int oldEnemyX = enemy.posX;
        int oldEnemyY = enemy.posY;

        // Обрабатываем ввод игрока и обновляем состояние игры
        game.handleInput(player, map);

        // Перемещаем курсор в начало консоли для перерисовки карты
        map.setCursor(0, 0);

        // после того как мы запомнили прошлые координаты, можно принять новые
        if(client->recv_command(enemy) < 0){
            delete client;
            system("pause");
            return -1;
        }

        // Обновляем карту с новыми позициями игрока и противника
        map.updateMap(enemy, oldEnemyX, oldEnemyY);
        map.updateMap(player, oldX, oldY);

        // Отображаем карту на экране
        map.display();

        // Задержка для плавности анимации
        Sleep(100);
    }

    // Освобождаем память и закрываем соединение
    delete client;

    return 0;
}
