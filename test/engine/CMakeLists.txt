add_executable(engine_test move_execution.cpp)
target_link_libraries(
        engine_test
        PRIVATE
        core
        GTest::gtest_main
)
gtest_discover_tests(engine_test WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")