add_executable(
        move_execution_test

        damage_util.h

        burn_tests.cpp
        confusion_tests.cpp
        critical_stage_tests.cpp
        curse_tests.cpp
        flinch_tests.cpp
        freeze_tests.cpp
        item_tests.cpp
        levitate_tests.cpp
        moonlight_tests.cpp
        paralysis_tests.cpp
        physical_attack_damage_tests.cpp
        sleep_tests.cpp
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

add_test(
        NAME move_execution_test
        COMMAND move_execution_test
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
