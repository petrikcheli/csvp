#include"game.h"

void Game::Map::setCursor(int x, int y){
    COORD pos {static_cast<SHORT>(x), static_cast<SHORT>(y)};
    HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(output, pos);
}

// void Game::BulletManager::addBullet(int x, int y, Bullet::Direction dir){
//     bullets.push_back({x, y, dir});
// }

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

void Game::updateBullets(Map& map, BulletManager& bulletArr) {
    for (auto it = bulletArr.bullets.begin(); it != bulletArr.bullets.end(); ) {
        int oldX = it->posX;
        int oldY = it->posY;

        switch (it->direction){
        case Bullet::RIGHT:
            it->posX += 1;
            break;
        case Bullet::LEFT:
            it->posX -= 1;
            break; 
        case Bullet::UP:
            it->posY -= 1;
            break;
        case Bullet::DOWN:
            it->posY += 1;
            break;
        }

        // Удаляем пулю, если она выходит за границы карты
        if (it->posX >= map.WIDTH || it->posX < 0 || it->posY >= map.HEIGHT || it->posY < 0) {
            it = bulletArr.bullets.erase(it);
        } else {
            // Обновляем карту с новой позицией пули
            if (oldY >= 0 && oldY < map.HEIGHT - 1 && oldX >= 0 && oldX < map.WIDTH) {
                map.gameMap[oldY][oldX] = ' ';
            }
            if (it->posY >= 1 && it->posY < map.HEIGHT - 1 && it->posX >= 1 && it->posX < map.WIDTH - 1) {
                map.gameMap[it->posY][it->posX] = (it->direction == Bullet::LEFT || it->direction == Bullet::RIGHT) ? '-' : '|';
            }
            ++it;
        }
    }
}

void Game::handleInput(Player& player, Map& map, BulletManager& bulletArr) {
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (player.posX > 2) {
            player.posX -= 2;
            player.lastDirection = Player::LEFT;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
        if (player.posX < map.WIDTH - 2) {
            player.posX += 2;
            player.lastDirection = Player::RIGHT;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
        if (player.posY < map.HEIGHT - 2) {
            player.posY++;
            player.lastDirection = Player::DOWN;
        }
    }
    if (GetAsyncKeyState(VK_UP) & 0x8000) {
        if (player.posY > 1) {
            player.posY--;
            player.lastDirection = Player::UP;
        }
    }

    __UINT32_TYPE__ currentTime = GetTickCount();

    if (GetAsyncKeyState(VK_SPACE) & 0x8000) { // Клавиша Space
        if(currentTime - lastShotTime >= shootInterval){
           switch (player.lastDirection){
            case Player::RIGHT:
                bulletArr.bullets.push_back({player.posX + 1, player.posY, Bullet::RIGHT});
                break;

            case Player::LEFT:
                bulletArr.bullets.push_back({player.posX - 1, player.posY, Bullet::LEFT});
                break;

            case Player::UP:
                bulletArr.bullets.push_back({player.posX, player.posY - 1, Bullet::UP});
                break;

            case Player::DOWN:
                bulletArr.bullets.push_back({player.posX, player.posY + 1, Bullet::DOWN});
                break;
            }
            lastShotTime = currentTime;
        }
    }
}

void Game::endGame(Player& player, BulletManager& bulletArr) {
    for (auto it = bulletArr.bullets.begin(); it != bulletArr.bullets.end(); ++it) {
        if (it->posX == player.posX && it->posY == player.posY) {
            isRunning = false;
            return;
        }
    }
}
