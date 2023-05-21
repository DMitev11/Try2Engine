cmake_minimum_required(VERSION 3.13)

set(
    HEADER_FILES
    render.hpp
    sdl_renderer.h
)

set(
    SOURCE_FILES
    sdl_renderer.cpp
)

add_library(render STATIC ${HEADER_FILES} ${SOURCE_FILES})

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
target_include_directories(render PUBLIC ${LIBRARY_OBJECTS_INCLUDE} ${SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR})
target_link_libraries(render PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)

set_target_properties(render PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
