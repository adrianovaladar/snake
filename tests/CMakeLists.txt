project(tests)

add_executable(AllTests ../tests/main.cpp ../tests/SnakeTests.cpp ../src/Snake.cpp RegularFoodTests.cpp ../src/RegularFood.cpp ../tests/BestScoresTests.cpp ../src/BestScores.cpp ../src/Player.cpp ../tests/GameTests.cpp ../src/Game.cpp ../src/Input.cpp ../src/Logger.cpp ../src/Food.cpp ../src/Food.h)
target_link_libraries(AllTests gtest gtest_main)
