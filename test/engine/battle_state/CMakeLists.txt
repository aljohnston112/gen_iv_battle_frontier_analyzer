add_library(
        battle_state_test
        OBJECT

        clear_body_tests.cpp
        slow_start_tests.cpp
        struggle_tests.cpp
        lum_berrry_tests.cpp
        get_move_tests.cpp
)

target_link_libraries(
        battle_state_test
        PRIVATE
        core
        GTest::gtest_main
        GTest::gmock
)