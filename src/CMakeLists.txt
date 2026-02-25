cmake_minimum_required(VERSION 3.20)
project(uno_game)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

add_executable(uno_game main.cpp src/Mazo.cpp src/Carta.cpp src/Juego.cpp)
