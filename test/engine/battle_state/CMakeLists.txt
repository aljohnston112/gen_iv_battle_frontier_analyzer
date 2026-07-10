add_executable(
        battle_state_test

        battle_state_tests.cpp
)

target_link_libraries(
        battle_state_test
        PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(battle_state_test WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")