add_library(
        serebii STATIC

        serebii_pokemon_data_source.cpp
        serebii_pokemon_data_source.h
)

target_include_directories(serebii PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(serebii PRIVATE common)
target_link_libraries(serebii PRIVATE models)
target_link_libraries(serebii PRIVATE simdjson)