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
}

void Game::Map::display(){
    for (const auto& line : gameMap) {
        std::cout << line << std::endl;
    }
}

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
}