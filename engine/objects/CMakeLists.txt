cmake_minimum_required(VERSION 3.13)

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

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(objects PUBLIC SDL_USED)
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
    target_include_directories(objects PUBLIC ${SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR})
    target_link_libraries(objects PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)
endif()

set_target_properties(objects PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
