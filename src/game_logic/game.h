#include<iostream>
#include<vector>
#include<Windows.h>

class Game{
public:
    // #define VK_W 0x57
    // #define VK_A 0x41
    // #define VK_S 0x53
    // #define VK_D 0x44
    bool isRunning = true;
    struct Player{
        char playerIcon = 'O';
        int posX = 0;
        int posY = 0;
        bool isAlive = true;
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

    // struct Shoot{
    //     int bulletPosX;
    //     int bulletPosY;
    //     char bulletIconX = '|';
    //     char bulletIconY = '-';
    //     bool direction = true; //true - x, false - y
    //     void bulletUpdate(Map& gameMap, int oldBulletPosX, int oldBulletPosY);
    // };

    void handleInput(Player& player, Map& map);
};