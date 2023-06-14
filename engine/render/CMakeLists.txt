cmake_minimum_required(VERSION 3.13)

set(
    HEADER_FILES
    render.hpp
)
set(
    SOURCE_FILES
)

if(DEFINED WITH_SDL AND WITH_SDL)
    set(HEADER_FILES
        ${HEADER_FILES}
        sdl_renderer.h)
    set(SOURCE_FILES
        ${SOURCE_FILES}
        sdl_renderer.cpp)
endif()

add_library(render STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(render PUBLIC ${LIBRARY_OBJECTS_INCLUDE} ${ENGINE_ROOT})
target_link_libraries(render INTERFACE logger)

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(render PUBLIC USE_SDL)
    target_include_directories(render PUBLIC ${SDL3_INCLUDE_DIRS})
    target_link_libraries(render PUBLIC ${SDL3_LIBRARIES})

    if(DEFINED WITH_SDL_IMAGE AND WITH_SDL_IMAGE)
        target_compile_definitions(render PUBLIC USE_SDL_IMAGE)
        target_include_directories(render PUBLIC ${SDLIMAGE_INCLUDE_DIR})
        target_link_libraries(render PUBLIC SDL3_image::SDL3_image)
    elseif(DEFINED WITH_STB AND WITH_STB)
        target_compile_definitions(render PUBLIC USE_STB)
    endif()
endif()

set_target_properties(render PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
