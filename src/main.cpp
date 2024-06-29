#include<iostream>
#include<vector>
#include<Windows.h>

bool isRunning = true;
char gameMap[] = 
    "###########################################################\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "#                                                         #\n"
    "###########################################################\n";

struct Player{    
    public:
        char playerIcon = 'O';
        int posX = 0;
        int posY = 0;
        bool isAlive;

        Player& operator=(const int other){
            if(posX == other || posY == other){
                return *this;
            }
        }
};

struct Map{
    public:
        const int WIDTH = 60;
        const int HEIGHT = 20;
        
        void setCursor(int x, int y){
            COORD pos {static_cast<SHORT>(x), static_cast<SHORT>(y)};
            HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleCursorPosition(output, pos);
        }
        void updateMap(char* map, int width, Player& player, int oldX, int oldY) {
            // Восстанавливаем символ на старой позиции
            int oldIndex = oldY * (width) + oldX;
            map[oldIndex] = ' ';
    
            // Заменяем символ игрока на новой позиции
            int newIndex = player.posY * (width) + player.posX;
            map[newIndex] = player.playerIcon;
        }
};

void handleInput(Player& player, const Map& map) {
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
        if (player.posX > 1) player.posX--;
    }
    if(GetAsyncKeyState(VK_RIGHT) & 0x8000){
        if(player.posX < map.WIDTH - 3) player.posX++;
    }
    if(GetAsyncKeyState(VK_DOWN) & 0x8000){
        if(player.posY < map.HEIGHT - 2) {
            player.posY++;
        }
    }
    if(GetAsyncKeyState(VK_UP) & 0x8000){
        if(player.posY > 1){
            player.posY--;
        } 
    }
}

int main(){
    Player player;
    Map map;
    player.posX = map.WIDTH / 2;
    player.posY = 1;

    while (isRunning){
        int oldX = player.posX;
        int oldY = player.posY;

        handleInput(player, map);
        
        map.setCursor(0, 0);
        map.updateMap(gameMap, map.WIDTH, player, oldX, oldY);
        std::cout << gameMap;
        Sleep(100);
    }
}