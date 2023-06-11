cmake_minimum_required(VERSION 3.13)
set(
    HEADER_FILES
    input_misc.h
    input.hpp
)
set(
    SOURCE_FILES
)

if(DEFINED WITH_SDL AND WITH_SDL)
    set(HEADER_FILES
        ${HEADER_FILES}
        sdl_input.h)
    set(SOURCE_FILES
        ${SOURCE_FILES}
        sdl_input.cpp)
endif()

add_library(input STATIC ${HEADER_FILES} ${SOURCE_FILES})

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(input PUBLIC SDL_USED)
    target_include_directories(input PUBLIC ${SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR})

    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
    target_link_libraries(input PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)
endif()

target_include_directories(input PUBLIC ${LIBRARY_OBJECTS_INCLUDE} ${ENGINE_ROOT})

set_target_properties(input PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
