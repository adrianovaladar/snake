cmake_minimum_required(VERSION 3.13)  # CMake version check
project(snake)                        # Create project "snake"
set(CMAKE_CXX_STANDARD 17)            # Enable c++17 standard

# Add source files
set(SOURCE_FILES src/main.cpp src/BestScores.h src/BestScores.cpp src/Food.h src/Food.cpp src/Game.h src/Game.cpp src/Input.h src/Input.cpp src/Player.h src/Player.cpp src/Snake.h src/Snake.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(snake ${SOURCE_FILES})