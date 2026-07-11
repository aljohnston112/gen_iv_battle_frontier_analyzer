cmake_minimum_required(VERSION 3.31)
project(gen_iv_battle_frontier_analyzer)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
    set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMMON_COMPILE_FLAGS
            -pthread
            -march=native
            -mbmi
            -mavx512f
            -mavx512bw
            -g
            -fno-omit-frame-pointer
            -Wall
            -Wextra
            -Wpedantic
            -Walloca
            -Warray-bounds=2
            -Wattribute-alias=2
            -Wbidi-chars=any
            -Wcast-qual
            -Wcomments
            -Wconversion
            -Wdisabled-optimization
            -Wduplicated-cond
            -Wflex-array-member-not-at-end
            -Wformat=2
            -Wformat-nonliteral
            -Wformat-overflow=2
            -Wshadow
            -Wformat-security
            -Wpacked
            -Wredundant-decls
            -Wnull-dereference
            -Wmultichar
            -Wstrict-overflow=5
            -Wnormalized=nfkc
            -Wformat-signedness
            -Wlogical-op
            -Wformat-truncation=2
            -Wformat-y2k
            -Wmissing-format-attribute
            -Wimplicit-fallthrough=5
            -Winit-self
            -Wstack-protector
            -Winvalid-utf8
            -Wstringop-overflow=4
            -Wfloat-equal
            -Wsuggest-attribute=cold
            -Wsuggest-attribute=const
            -Wsuggest-attribute=format
            -Wsuggest-attribute=malloc
            -Wsuggest-attribute=noreturn
            -Wsuggest-attribute=pure
            -Wsuggest-attribute=returns_nonnull
            -Wswitch-enum
            -Wswitch-default
            -Wduplicated-branches
            -Wtrivial-auto-var-init
            -ftrivial-auto-var-init=pattern
            -Wunused-macros
            -Wwrite-strings
            -Wzero-as-null-pointer-constant
            -Wuse-after-free=3
            --strict-flex-arrays=3
            -Wanalyzer-symbol-too-complex
            -fstack-clash-protection
            -Wframe-larger-than=8388608
            -Wstack-usage=8388608
            -fstack-usage
            -fstack-protector
            --param=analyzer-max-svalue-depth=50
            -mtune=native
            -fno-inline
    )
else ()
    set(COMMON_COMPILE_FLAGS)
endif ()

add_compile_options(${COMMON_COMPILE_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto")

find_package(OpenMP REQUIRED)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

add_subdirectory(external)
add_subdirectory(src)

add_library(core INTERFACE)
target_link_libraries(core INTERFACE
        battle_factory
        common
        engine
        models
        serebii
        simdjson
)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION FALSE)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/973323ed64a05b128418e7eab67016db5ba049df.zip
)
FetchContent_MakeAvailable(googletest)

add_subdirectory(test)

add_custom_target(
        build_all_tests DEPENDS

        battle_engine_test
        battle_state_test
        move_execution_test
)

add_custom_target(run_tests DEPENDS build_all_tests
        COMMAND ${CMAKE_CTEST_COMMAND}
        --test-dir "${CMAKE_BINARY_DIR}/test"
        --output-on-failure
        COMMENT "Running tests via ctest..."
        VERBATIM
)
