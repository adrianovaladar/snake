# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(AllTests ../tests/main.cpp ../tests/SnakeTests.cpp ../src/Snake.cpp ../tests/FoodTests.cpp ../src/Food.cpp ../tests/BestScoresTests.cpp ../src/BestScores.cpp ../src/Player.cpp)
target_link_libraries(AllTests gtest gtest_main)
