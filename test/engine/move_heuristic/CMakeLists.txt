add_executable(
        move_heuristic_test

        move_heuristic_test.cpp
)

target_link_libraries(
        move_heuristic_test
        PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(move_heuristic_test WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")