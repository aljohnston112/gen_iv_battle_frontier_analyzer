add_executable(
        battle_state_test

        slow_start_tests.cpp
        struggle_tests.cpp
)

target_link_libraries(
        battle_state_test
        PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(battle_state_test WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")