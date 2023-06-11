cmake_minimum_required(VERSION 3.12)

# Set project name
project(Try1 LANGUAGES CXX)

set(HEADER_FILES
    inc/Try1.h
)
set(SOURCE_FILES
    main.cpp
    src/Try1.cpp)
add_executable(try1 ${SOURCE_FILES})

target_compile_features(try1 PUBLIC cxx_std_17)
target_link_libraries(try1 PUBLIC utils window render loader logger input)
target_include_directories(try1 PUBLIC ${ENGINE_ROOT} ${CMAKE_CURRENT_SOURCE_DIR}/)

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(try1 PUBLIC SDL_USED)
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)

    target_include_directories(try1 PUBLIC ${SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR})
    target_link_libraries(try1 PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)
endif()

message(STATUS "Engine Folder: ${CMAKE_SOURCE_DIR}/engine")
message(STATUS "Source Folder: ${PROJECT_SOURCE_DIR} ")
set_target_properties(try1 PROPERTIES
    CXX_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)

# copy SDL binaries
get_target_property(runtime_folder try1 RUNTIME_OUTPUT_DIRECTORY_DEBUG)

if(DEFINED WITH_SDL AND WITH_SDL)
    add_custom_command(
        TARGET try1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_BIN}/ ${runtime_folder}/
        COMMENT "Copy SDL3 dynamic binaries")

    add_custom_command(
        TARGET try1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_image_BIN}/ ${runtime_folder}/
        COMMENT "Copy SDL3_image dynamic binaries")
endif()

add_custom_command(
    TARGET try1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${runtime_folder}/assets
    COMMENT "Copy assets")
