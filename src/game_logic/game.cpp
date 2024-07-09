#include"game.h"

void Game::Map::setCursor(int x, int y){
    COORD pos {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

void Game::Map::updateMap(Game::Player& player, int oldX, int oldY) {
// Восстанавливаем символ на старой позиции
    if (oldY >= 0 && oldY < HEIGHT && oldX >= 0 && oldX < WIDTH) {
        gameMap[oldY][oldX] = ' ';
    }

    if (player.posY >= 0 && player.posY < HEIGHT && player.posX >= 0 && player.posX < WIDTH) {
        gameMap[player.posY][player.posX] = player.playerIcon;
    }
}

void Game::Map::display(){
    for (const auto& line : gameMap) {
        std::cout << line << std::endl;
    }
}

// void Game::Shoot::bulletUpdate(Game::Map& gm, int oldBulletPosX, int oldBulletPosY){
//     if (oldBulletPosY >= 0 && oldBulletPosY < gm.HEIGHT && oldBulletPosX >= 0 && oldBulletPosX < gm.WIDTH) {
//         gm.gameMap[oldBulletPosY][oldBulletPosX] = ' ';
//     }

//     char bulletIcon = direction ? bulletIconX : bulletIconY;

//     if(bulletPosY >= 0 && bulletPosY < gm.HEIGHT && bulletPosX >= 0 && bulletPosX < gm.WIDTH){
//         gm.gameMap[bulletPosY][bulletPosX] = bulletIcon;

//         oldBulletPosX = bulletPosX;
//         oldBulletPosY = bulletPosY;

//         bulletPosX += 1;
//         bulletPosY += (direction ? 1 : -1);
//         Sleep(200);
//         Game::Shoot::bulletUpdate(gm, oldBulletPosX, oldBulletPosY);
//     }
//     else {
//         bulletIcon = ' ';
//         gm.gameMap[bulletPosY][bulletPosX] = bulletIcon;
//     }
// }

void Game::handleInput(Player& player, Map& map) {
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (player.posX > 2) {
            player.posX -= 2;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if (player.posX < map.WIDTH - 2) {
            player.posX += 2;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if (player.posY < map.HEIGHT - 2) {
            player.posY++;
        }
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        if (player.posY > 1) {
            player.posY--;
        }
    }

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // Клавиша Space
        // if (shoot.bulletPosX == -1 && shoot.bulletPosY == -1) {
        //     // Устанавливаем начальную позицию пули рядом с игроком
        //     if (shoot.direction) { // Если направление - горизонталь
        //         shoot.bulletPosX = player.posX + 1;
        //         shoot.bulletPosY = player.posY;
        //         shoot.bulletUpdate(map, oldBulletPosX, oldBulletPosY);
        //     } 
        //     else { // Если направление - вертикаль
        //         shoot.bulletPosX = player.posX;
        //         shoot.bulletPosY = player.posY - 1;
        //         shoot.bulletUpdate(map, oldBulletPosX, oldBulletPosY);
        //     }
        // }
    }
}