add_library(
        simdjson STATIC

        simdjson.cpp
        simdjson.h
)

target_include_directories(simdjson PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")