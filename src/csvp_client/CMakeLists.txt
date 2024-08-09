cmake_minimum_required(VERSION 3.5)

project(csvp_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS thread filesystem system program_options date_time REQUIRED)

if (${Boost_FOUND})
    message("Found Boost " ${Boost_VERSION})
else()
    message("Couldn't find Boost")
endif()

add_executable(csvp_client
    #main.cpp
    udp_main.cpp
    udp_client.h udp_client.cpp
    #client.cpp client.h
    ../game_logic/game.cpp ../game_logic/game.h
    ../game_logic/screensaver.h)

target_link_libraries(csvp_client Boost::thread Boost::filesystem Boost::system
    Boost::program_options Boost::date_time)

if(WIN32)
  target_link_libraries(csvp_client wsock32 ws2_32)
endif()
