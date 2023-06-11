cmake_minimum_required(VERSION 3.12)

set(
    HEADER_FILES
    event_emitter.hpp
    layer.h
    entry_point.h
)

add_library(utils STATIC ${HEADER_FILES})

set_target_properties(utils PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)