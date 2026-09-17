add_library(
        battle_engine_test
        OBJECT

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