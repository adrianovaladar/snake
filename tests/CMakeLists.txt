project(tests)

add_executable(AllTests ../tests/main.cpp ../tests/SnakeTests.cpp ../src/Snake.cpp FoodTests.cpp ../src/RegularFood.cpp ../tests/BestScoresTests.cpp ../src/BestScores.cpp ../src/Player.cpp ../tests/GameTests.cpp ../src/Game.cpp ../src/Input.cpp ../src/Logger.cpp ../src/Food.cpp ../src/Food.h ../src/SuperFood.cpp ../src/SuperFood.h)
target_link_libraries(AllTests gtest gtest_main)
