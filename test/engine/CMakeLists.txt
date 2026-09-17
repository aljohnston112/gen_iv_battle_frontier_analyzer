add_subdirectory(battle_engine)
add_subdirectory(battle_state)
add_subdirectory(move_execution)
add_subdirectory(move_heuristic)

add_executable(all_tests)

target_sources(
        all_tests
        PRIVATE

        $<TARGET_OBJECTS:battle_engine_test>
        $<TARGET_OBJECTS:battle_state_test>
        $<TARGET_OBJECTS:move_execution_test>
        $<TARGET_OBJECTS:move_heuristic_test>
)

target_link_libraries(
        all_tests
        PRIVATE

        core

        GTest::gtest_main
)