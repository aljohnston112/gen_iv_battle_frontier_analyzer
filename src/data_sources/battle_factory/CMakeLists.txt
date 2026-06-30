add_library(
        battle_factory STATIC

        factory_data_source.cpp
        factory_data_source.h
)

target_include_directories(battle_factory PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(battle_factory PRIVATE common)
target_link_libraries(battle_factory PRIVATE models)
target_link_libraries(battle_factory PRIVATE serebii)
target_link_libraries(battle_factory PRIVATE simdjson)