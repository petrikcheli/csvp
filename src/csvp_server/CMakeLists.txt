cmake_minimum_required(VERSION 3.5)

project(csvp_server LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(csvp_server main.cpp server.cpp server.h)

if(WIN32)
  target_link_libraries(csvp_server wsock32 ws2_32)
endif()
