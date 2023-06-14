cmake_minimum_required(VERSION 3.13)

set(
    HEADER_FILES
    loader.hpp
)

set(
    SOURCE_FILES
)

if(DEFINED WITH_SDL AND WITH_SDL)
    set(HEADER_FILES
        ${HEADER_FILES}
        sdl_loader.h)

    set(SOURCE_FILES
        ${SOURCE_FILES}
        sdl_loader.cpp)
endif()

add_library(loader STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(loader INTERFACE logger)
target_include_directories(loader PUBLIC ${LIBRARY_OBJECTS_INCLUDE})
target_include_directories(loader PUBLIC ${ENGINE_ROOT})

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(loader PUBLIC USE_SDL)
    target_include_directories(loader PUBLIC ${SDL3_INCLUDE_DIRS})
    target_link_libraries(loader PUBLIC ${SDL3_LIBRARIES})

    if(DEFINED WITH_SDL_IMAGE AND WITH_SDL_IMAGE)
        target_compile_definitions(loader PUBLIC USE_SDL_IMAGE)
        target_include_directories(loader PUBLIC ${SDLIMAGE_INCLUDE_DIR})
        target_link_libraries(loader PUBLIC SDL3_image::SDL3_image)
    elseif(DEFINED WITH_STB AND WITH_STB)
        target_compile_definitions(loader PUBLIC USE_STB)
    endif()
endif()

set_target_properties(loader PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
