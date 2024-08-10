#include <iostream>
#include "udp_client.h"
//#include <windows.h>
//#include <boost/asio.hpp>
#include "../game_logic/game.h"
#include "../game_logic/screensaver.h"

using namespace boost::asio;
using namespace std;


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

int main(){
    io_service service;
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

    Udp_client client = service;

    client.initialization_players(player, enemy);

    while(game.isRunning){

        // отправляем данные на сервер
        client.send_data_player(player, playerBullet);

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
        client.recv_data_enemy(enemy, enemyBullet);

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
    //delete client;

    return 0;
}
