cmake_minimum_required(VERSION 3.13)  # CMake version check
project(snake)                        # Create project "snake"
set(CMAKE_CXX_STANDARD 23)            # Enable c++23 standard

# Add source files
set(SOURCE_FILES src/main.cpp src/BestScores.h src/BestScores.cpp src/Food.h src/Food.cpp src/Game.h src/Game.cpp src/Input.h src/Input.cpp src/Player.h src/Player.cpp src/Snake.h src/Snake.cpp src/Logger.cpp src/Logger.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(snake ${SOURCE_FILES})

# Add GTest
add_subdirectory(third_party/Google_tests)

# Add tests
add_subdirectory(tests)