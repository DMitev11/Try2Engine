cmake_minimum_required(VERSION 3.15)

add_library(logger STATIC logger.h logger.cpp)
target_include_directories(logger PUBLIC ${SPDLOG_INCLUDE_DIRS})
set_target_properties(logger PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
