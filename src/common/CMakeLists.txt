add_library(common STATIC config.h util.h)

target_include_directories(common PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)
