cmake_minimum_required(VERSION 3.5)

project(csvp_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(csvp_client main.cpp client.cpp client.h ../game_logic/game.cpp ../game_logic/game.h
    ../game_logic/screensaver.h)

if(WIN32)
  target_link_libraries(csvp_client wsock32 ws2_32)
endif()
