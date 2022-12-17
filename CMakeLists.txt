cmake_minimum_required(VERSION 3.24)
project(adventofcode2022)

# Find all the files in the data folder
file(GLOB DATA_FILES "${CMAKE_SOURCE_DIR}/data/*")

# Copy the data files to the build directory
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 23)

add_executable(adventofcode2022 main.cpp day01.cpp day02.cpp file.cpp file.hpp)
