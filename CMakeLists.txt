cmake_minimum_required(VERSION 3.6)  # CMake version check
project(DBDS)
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES src/main.cpp src/container.hpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(DBDS ${SOURCE_FILES})