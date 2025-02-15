project(tests)

add_executable(AllTests ../tests/main.cpp ../tests/SnakeTests.cpp ../src/Snake.cpp FoodTests.cpp ../tests/BestScoresTests.cpp ../src/BestScores.cpp ../src/Player.cpp ../tests/GameTests.cpp ../src/Game.cpp ../src/Input.cpp ../src/Logger.cpp ../src/Food.cpp ../src/Food.h ../src/SuperFood.cpp ../src/SuperFood.h ../src/Utils.cpp ../src/Utils.h SnakeTests.h GameTests.h)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(AllTests gtest gtest_main gmock_main)
