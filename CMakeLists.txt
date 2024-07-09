cmake_minimum_required(VERSION 3.5)
project(CSVP LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_executable(csvp
    src/game_logic/game.cpp
    src/game_logic/game.h
    src/game_logic/game_main.cpp
)