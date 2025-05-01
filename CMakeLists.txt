cmake_minimum_required(VERSION 3.26)  # CMake version check
project(snake)                        # Create project "snake"
set(CMAKE_CXX_STANDARD 23)            # Enable c++23 standard

option(BUILD_COVERAGE "Enable coverage reporting" OFF)
if (BUILD_COVERAGE)
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
endif ()

# Add source files
set(SOURCE_FILES src/main.cpp src/BestScores.h src/BestScores.cpp src/Game.h src/Game.cpp src/Input.h src/Input.cpp src/Player.h src/Player.cpp src/Snake.h src/Snake.cpp src/Food.cpp src/Food.h src/SuperFood.cpp src/SuperFood.h src/Utils.cpp src/Utils.h src/Graphics.cpp src/Graphics.h)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(snake ${SOURCE_FILES})

include(FetchContent)

FetchContent_Declare(
        LOGorithm
        GIT_REPOSITORY https://github.com/adrianovaladar/LOGorithm.git
        GIT_TAG 1.0
)
FetchContent_MakeAvailable(LOGorithm)
target_link_libraries(snake PRIVATE LOGorithm)

# Add tests - Only if BUILD_TESTS is enabled
option(BUILD_TESTS "Build tests" OFF)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()
