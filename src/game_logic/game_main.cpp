#include"game.h"

int main() {
    Game game;
    Game::Player player;
    Game::Map map;
    Game::Player enemy;
    // Game::Shoot shoot;

    // Инициализация позиций игрока и врага
    player.posX = map.WIDTH / 2;
    player.posY = 1;

    // shoot.bulletPosX = map.WIDTH / 2;
    // shoot.bulletPosY = 2;

    enemy.posX = map.WIDTH / 2;
    enemy.posY = map.HEIGHT - 2;

    // Основной цикл игры
    while (game.isRunning) {
        int oldX = player.posX;
        int oldY = player.posY;

        int oldEnemyX = enemy.posX;
        int oldEnemyY = enemy.posY;

        // int oldBulletPosX = shoot.bulletPosX;
        // int oldBulletPosY = shoot.bulletPosY;

        game.handleInput(player, map);

        // Обновление карты и курсора
        map.setCursor(0, 0);
        // shoot.bulletUpdate(map, oldBulletPosX, oldBulletPosY);
        map.updateMap(player, oldX, oldY);
        map.updateMap(enemy, oldEnemyX, oldEnemyY);

        map.display();
        Sleep(100);
    }

    return 0;
}