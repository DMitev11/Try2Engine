cmake_minimum_required(VERSION 3.15)

set(
    HEADER_FILES
    window_object.h
    renderer_object.h
    texture_object.h
)
set(
    SOURCE_FILES
)

if(DEFINED WITH_SDL AND WITH_SDL)
    set(HEADER_FILES
        ${HEADER_FILES}
        sdl_window_object.h
        sdl_renderer_object.h
        sdl_texture_object.h)

    set(SOURCE_FILES ${SOURCE_FILES})
endif()

add_library(objects STATIC ${HEADER_FILES})

set_target_properties(objects PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
