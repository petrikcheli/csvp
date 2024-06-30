#include<iostream>
#include<vector>
#include<Windows.h>

class Game{
public:
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
    void handleInput(Player& player, Map& map);
};