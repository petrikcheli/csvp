cmake_minimum_required(VERSION 3.5)

project(linux_server_csvp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS thread filesystem system program_options date_time REQUIRED)

if (${Boost_FOUND})
    message("Found Boost " ${Boost_VERSION})
else()
    message("Couldn't find Boost")
endif()

add_executable(linux_server_csvp
    #main.cpp
    main_upd.cpp
    #server.h server.cpp
    #game.h game.cpp
    ../game_logic/game.h
    udp_server.h udp_server.cpp
    )

target_link_libraries(linux_server_csvp Boost::thread Boost::filesystem Boost::system
    Boost::program_options Boost::date_time)
if(WIN32)
  target_link_libraries(linux_server_csvp wsock32 ws2_32)
endif()
#else()
#    include(GNUInstallDirs)
#    install(TARGETS linux_server_csvp
#        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
#    )
#endif()

