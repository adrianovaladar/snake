project(tests)

add_executable(AllTests ../tests/main.cpp ../tests/SnakeTests.cpp ../src/Snake.cpp ../tests/FoodTests.cpp ../src/Food.cpp ../tests/BestScoresTests.cpp ../src/BestScores.cpp ../src/Player.cpp ../tests/GameTests.cpp ../src/Game.cpp ../src/Input.cpp ../src/Logger.cpp)
target_link_libraries(AllTests gtest gtest_main)
