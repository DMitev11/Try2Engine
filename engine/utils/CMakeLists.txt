cmake_minimum_required(VERSION 3.12)

set(
    HEADER_FILES
    event_emitter.hpp
    layer_stack.h
    layer.h
    entry.h
)

set(SOURCE_FILES
    layer_stack.cpp)

add_library(utils STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(utils PUBLIC ${LIBRARY_OBJECTS_INCLUDE} ${ENGINE_ROOT})
target_link_libraries(utils INTERFACE logger)

set_target_properties(utils PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)