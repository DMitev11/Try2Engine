cmake_minimum_required(VERSION 3.13)

set(
    HEADER_FILES
    window.hpp
)

set(
    SOURCE_FILES
)

if(DEFINED WITH_SDL AND WITH_SDL)
    set(HEADER_FILES
        ${HEADER_FILES}
        sdl_window.h)
    set(SOURCE_FILES
        ${SOURCE_FILES}
        sdl_window.cpp)
endif()

add_library(window STATIC ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(window PUBLIC ${LIBRARY_OBJECTS_INCLUDE} ${ENGINE_ROOT})
target_link_libraries(window INTERFACE logger)

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(window PUBLIC USE_SDL)
    target_include_directories(window PUBLIC {SDL3_INCLUDE_DIRS})
    target_link_libraries(window PUBLIC ${SDL3_LIBRARIES})
endif()

set_target_properties(window PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
