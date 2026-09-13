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

add_test(
        NAME move_heuristic_test
        COMMAND move_heuristic_test
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
