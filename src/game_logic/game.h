#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<vector>
//#include<Windows.h>

class Game{
public:
    // #define VK_W 0x57
    // #define VK_A 0x41
    // #define VK_S 0x53
    // #define VK_D 0x44

     __UINT32_TYPE__ lastShotTime = 0;
    const __UINT32_TYPE__ shootInterval = 500; //расчёт в милисекундах

    bool isRunning = true;
    struct Player{
        char playerIcon = 'O';
        int posX = 0;
        int posY = 0;
        bool isAlive = true;
        enum Direction { UP, DOWN, LEFT, RIGHT } lastDirection;
    };
    struct Map{
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
        const int WIDTH = 60;
        const int HEIGHT = 20;

        void setCursor(int x, int y);
        void updateMap(Player& player, int oldX, int oldY);
        void display();
    };

    struct Bullet{
        int posX;
        int posY;
        // bool direction;
        enum Direction { UP, DOWN, LEFT, RIGHT } direction;
    };

    struct BulletManager{
        std::vector<Bullet> bullets;
    };

    void updateBullets(Map& map, BulletManager& bulletArr);
    void handleInput(Player& player, Map& map, BulletManager& bulletArr);
    void endGame(Player& player, BulletManager& bulletArr);
};

#endif // GAME_H
