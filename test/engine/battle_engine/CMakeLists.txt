add_executable(
        battle_engine_test

        flash_fire_tests.cpp
        sleep_tests.cpp
        curse_tests.cpp
)

target_link_libraries(
        battle_engine_test
        PRIVATE
        core
        GTest::gtest_main
)

add_test(
        NAME battle_engine_test
        COMMAND battle_engine_test
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
