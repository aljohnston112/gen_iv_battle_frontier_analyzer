add_executable(
        battle_engine_test

        flash_fire_tests.cpp
)

target_link_libraries(
        battle_engine_test
        PRIVATE
        core
        GTest::gtest_main
)

gtest_discover_tests(battle_engine_test WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")