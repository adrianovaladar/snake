project(tests)

add_executable(AllTests main.cpp SnakeTests.cpp ../src/Snake.cpp FoodTests.cpp FoodTests.h BestScoresTests.cpp ../src/BestScores.cpp ../src/Player.cpp GameTests.cpp ../src/Game.cpp ../src/Input.cpp ../src/Food.cpp ../src/Food.h ../src/SuperFood.cpp ../src/SuperFood.h ../src/Utils.cpp ../src/Utils.h SnakeTests.h GameTests.h ../src/Graphics.cpp ../src/Graphics.h)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_Declare(
        LOGorithm
        GIT_REPOSITORY https://github.com/adrianovaladar/LOGorithm.git
        GIT_TAG 1.0
)
FetchContent_MakeAvailable(LOGorithm)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
target_link_libraries(AllTests gtest gtest_main gmock_main LOGorithm)
