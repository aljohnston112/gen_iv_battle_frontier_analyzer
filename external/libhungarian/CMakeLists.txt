add_library(
        libhungarian STATIC

        hungarian.c
        hungarian.h
)

target_include_directories(libhungarian PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")