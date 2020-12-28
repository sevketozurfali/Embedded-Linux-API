cmake_minimum_required(VERSION 3.17)
project(ADS1115_1015 C)

set(CMAKE_C_STANDARD 99)

add_executable(ADS1115_1015 main.c libs/ADS1115-1015.c libs/ADS1115-1015.h)