#include <iostream>
#include <vector>
#include <Windows.h>

// Глобальная переменная для работы цикла
bool isRunning = true;

// Структура для игрока
struct Player {
    char playerIcon = 'O';
    int posX = 0;
    int posY = 0;
    bool isAlive = true;
};

// Структура для карты
struct Map {
    const int WIDTH = 60;
    const int HEIGHT = 20;
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

    // Функция для установки позиции курсора
    void setCursor(int x, int y) {
        COORD pos{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(output, pos);
    }

    // Функция для обновления карты
    void updateMap(Player& player, int oldX, int oldY) {
        // Восстанавливаем символ на старой позиции
        if (oldY >= 0 && oldY < HEIGHT && oldX >= 0 && oldX < WIDTH) {
            gameMap[oldY][oldX] = ' ';
        }

        // Заменяем символ игрока на новой позиции
        if (player.posY >= 0 && player.posY < HEIGHT && player.posX >= 0 && player.posX < WIDTH) {
            gameMap[player.posY][player.posX] = player.playerIcon;
        }
    }

    // Вывод карты
    void display() {
        for (const auto& line : gameMap) {
            std::cout << line << std::endl;
        }
    }
};

// Функция для обработки ввода пользователя
void handleInput(Player& player, Map& map) {
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

int main() {
    Player player;
    Map map;
    Player enemy;

    // Инициализация позиций игрока и врага
    player.posX = map.WIDTH / 2;
    player.posY = 1;

    enemy.posX = map.WIDTH / 2;
    enemy.posY = map.HEIGHT - 2;

    // Основной цикл игры
    while (isRunning) {
        int oldX = player.posX;
        int oldY = player.posY;

        int oldEnemyX = enemy.posX;
        int oldEnemyY = enemy.posY;

        handleInput(player, map);

        // Обновление карты и курсора
        map.setCursor(0, 0);
        map.updateMap(player, oldX, oldY);
        map.updateMap(enemy, oldEnemyX, oldEnemyY);

        map.display();
        Sleep(100);
    }

    return 0;
}
