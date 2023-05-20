cmake_minimum_required(VERSION 3.13)

set(
    HEADER_FILES
    window_object.h
    sdl_window_object.h
    renderer_object.h
)

set(
    SOURCE_FILES 
)

add_library(objects STATIC ${HEADER_FILES} ${SOURCE_FILES})

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)  
target_include_directories(objects PUBLIC ${SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR})
target_link_libraries(objects PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)

set_target_properties(objects PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
