add_library(
        models STATIC

        ability.h
        category.h
        item.h
        move.h
        nature.h
        pokemon.h
        stat.h
        type.h
)

target_include_directories(models PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
set_target_properties(models PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(models PRIVATE common)