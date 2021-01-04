cmake_minimum_required(VERSION 3.17)
project(AD7298 C)

set(CMAKE_C_STANDARD 99)

add_executable(AD7298 main.c libs/ad7298.h libs/ad7298.c)