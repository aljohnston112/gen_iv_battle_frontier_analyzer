add_library(
        engine STATIC

        battle_engine.h
        battle_state.h
        end_of_turn_effects.h
        move_execution.h
        move_heuristic.h
        policies.h
        round_robin.h
        thread_pool.h
        thread_pool.cpp
)

target_include_directories(engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(engine PRIVATE common)
target_link_libraries(engine PRIVATE models)
target_link_libraries(engine PRIVATE serebii)
target_link_libraries(engine PRIVATE battle_factory)
