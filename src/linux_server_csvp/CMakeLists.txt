cmake_minimum_required(VERSION 3.5)

project(linux_server_csvp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(linux_server_csvp main.cpp
    server.h server.cpp
    #game.h game.cpp
    ../game_logic/game.h
    )

include(GNUInstallDirs)
install(TARGETS linux_server_csvp
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
