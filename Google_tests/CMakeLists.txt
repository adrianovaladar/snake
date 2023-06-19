# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'SnakeTests' is the target name
# 'SnakeTests.cpp' is a source file with tests
# 'Snake.cpp' is the source file that will be tested
add_executable(SnakeTests ../tests/SnakeTests.cpp ../src/Snake.cpp)
target_link_libraries(SnakeTests gtest gtest_main)
add_executable(FoodTests ../tests/FoodTests.cpp ../src/Food.cpp)
target_link_libraries(FoodTests gtest gtest_main)
add_executable(BestScoresTests ../tests/BestScoresTests.cpp ../src/BestScores.cpp ../src/Player.cpp)
target_link_libraries(BestScoresTests gtest gtest_main)