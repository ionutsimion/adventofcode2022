cmake_minimum_required(VERSION 3.24)
project(adventofcode2022)

set(CMAKE_CXX_STANDARD 23)

add_executable(adventofcode2022 main.cpp day01.cpp day02.cpp file.cpp file.hpp day03.cpp day04.cpp day05.cpp day06.cpp day07.cpp)
file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION ${CMAKE_BINARY_DIR})

install(TARGETS adventofcode2022 DESTINATION ${CMAKE_BINARY_DIR}/bin)
file(COPY "${CMAKE_SOURCE_DIR}/data" DESTINATION ${CMAKE_BINARY_DIR}/bin)
