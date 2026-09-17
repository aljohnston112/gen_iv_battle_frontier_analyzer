add_library(
        move_heuristic_test
        OBJECT

        move_heuristic_test.cpp
)

target_link_libraries(
        move_heuristic_test
        PRIVATE
        core
        GTest::gtest_main
)
