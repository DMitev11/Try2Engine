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
target_include_directories(input PUBLIC ${LIBRARY_OBJECTS_INCLUDE} ${ENGINE_ROOT})

set_target_properties(input PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(input PUBLIC SDL_USED)
    target_include_directories(input PUBLIC ${SDL3_INCLUDE_DIRS})
    target_link_libraries(input PUBLIC ${SDL3_LIBRARIES})
endif()

if(DEFINED WITH_IMGUI AND WITH_IMGUI)
    target_compile_definitions(input PUBLIC IMGUI_USED)
    target_link_libraries(input PUBLIC imgui)
    target_include_directories(input PUBLIC ${IMGUI_DIR})
endif()
