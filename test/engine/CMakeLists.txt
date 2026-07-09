add_executable(
        engine_test

        mocks.h

        battle_engine/pp_tests.cpp

        move_execution/confusion_tests.cpp
        move_execution/special_attack_damage_tests.cpp
        move_execution/move_execution_test.cpp
        move_execution/struggle_tests.cpp
        move_execution/stat_change_tests.cpp
        move_execution/moonlight_tests.cpp
)

target_link_libraries(
        engine_test
        PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(engine_test WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")