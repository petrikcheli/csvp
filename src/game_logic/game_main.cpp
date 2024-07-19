#include"game.h"
#include"screensaver.h"

int main() {
    Game game;
    Game::Player player;
    Game::Map map;
    Game::Player enemy;
    Game::BulletManager playerBullet;
    Game::BulletManager enemyBullet;

    Rocket rocket;

    // Инициализация позиций игрока и врага
    player.posX = map.WIDTH / 2;
    player.posY = 1;

    enemy.posX = map.WIDTH / 2;
    enemy.posY = map.HEIGHT - 2;

    // rocket.printScreenSaver();

    // Основной цикл игры
    while (game.isRunning) {
        int oldX = player.posX;
        int oldY = player.posY;

        int oldEnemyX = enemy.posX;
        int oldEnemyY = enemy.posY;

        game.handleInput(player, map, playerBullet);

        // Обновление карты и курсора
        map.setCursor(0, 0);
        game.updateBullets(map, playerBullet);
        game.updateBullets(map, enemyBullet);
        map.updateMap(player, oldX, oldY);
        map.updateMap(enemy, oldEnemyX, oldEnemyY);

        game.endGame(enemy, playerBullet);
        game.endGame(player, enemyBullet);

        map.display();
        Sleep(100);
    }

    return 0;
}