cmake_minimum_required(VERSION 3.24)
project(Gra_2048 C)

set(CMAKE_C_STANDARD 11)

add_executable(Gra_2048
        main.c
        game.h
        game.c
        oled_game.h
        oled_game.c
        )