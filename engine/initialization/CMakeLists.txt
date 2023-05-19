cmake_minimum_required(VERSION 3.13)

set(
    HEADER_FILES
    initialization.h   
    sdl_initialization.h   
)

set(
    SOURCE_FILES   
    sdl_initialization.cpp
)

add_library(initialization ${HEADER_FILES} ${SOURCE_FILES})

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)

target_include_directories(initialization PUBLIC ${SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR})
target_link_libraries(initialization PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)

set_target_properties(initialization PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
