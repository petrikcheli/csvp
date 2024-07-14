#include"screensaver.h"

void Rocket::printScreenSaver(){
    for(auto line : picture){
        std::cout << line << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::seconds(4));
    system("cls");
}