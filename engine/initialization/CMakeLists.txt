cmake_minimum_required(VERSION 3.13)

set(
    HEADER_FILES
    initialization.hpp
)

set(
    SOURCE_FILES
)

if(DEFINED WITH_SDL AND WITH_SDL)
    set(
        HEADER_FILES
        ${HEADER_FILES}
        sdl_initialization.h
    )

    set(
        SOURCE_FILES
        ${SOURCE_FILES}
        sdl_initialization.cpp
    )
endif()

add_library(initialization ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(initialization INTERFACE logger)
target_include_directories(initialization PUBLIC ${ENGINE_ROOT})

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(initialization PUBLIC SDL_USED)
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)

    target_include_directories(initialization PUBLIC ${SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR})
    target_link_libraries(initialization PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)
endif()

set_target_properties(initialization PROPERTIES
    LINKER_LANGUAGE CXX_STANDARD
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
