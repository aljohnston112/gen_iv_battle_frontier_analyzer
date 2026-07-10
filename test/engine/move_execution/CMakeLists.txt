add_executable(
        move_execution_test

        confusion_tests.cpp
        moonlight_tests.cpp
        move_execution_test.cpp
        special_attack_damage_tests.cpp
        stat_change_tests.cpp
        struggle_tests.cpp
)

target_link_libraries(
        move_execution_test
        PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(move_execution_test WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")