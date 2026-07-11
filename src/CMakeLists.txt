add_subdirectory(common)
add_subdirectory(models)
add_subdirectory(data_sources)
add_subdirectory(engine)

add_executable(gen_iv_battle_frontier_analyzer main.cpp)
target_link_libraries(
        gen_iv_battle_frontier_analyzer PRIVATE
        core
        OpenMP::OpenMP_CXX
)

function(add_data_copy_post_build target_name)
    add_custom_command(
            TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/data"
            "${CMAKE_BINARY_DIR}/data"
            COMMENT "Copying data assets"
            VERBATIM
    )
endfunction()

add_data_copy_post_build(gen_iv_battle_frontier_analyzer)