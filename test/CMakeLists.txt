enable_testing()
include(CTest)
include(GoogleTest)

add_executable(test_runner test_runner.cpp)
target_link_libraries(
        test_runner
        PRIVATE
        core
        GTest::gtest_main
)
gtest_discover_tests(test_runner WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")

add_subdirectory(engine)
