cmake_minimum_required(VERSION 3.25)
project(battleship C)

set(CMAKE_C_STANDARD 11)

add_executable(battleship
        game.c
        game.h
        main.c
        menu.c
        menu.h
        tile_map_management.c
        tile_map_management.h)

target_link_libraries(battleship PUBLIC
        winMM.Lib)