cmake_minimum_required(VERSION 3.12)

# Set project name
project(Application LANGUAGES CXX)

set(HEADER_FILES
    main.h
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/Visualizer.h)
set(SOURCE_FILES
    main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/objects/Visualizer.cpp)
add_executable(application ${HEADER_FILES} ${SOURCE_FILES})

target_compile_features(application PUBLIC cxx_std_17)
target_link_libraries(application PUBLIC window initialization render loader)
target_include_directories(application PUBLIC ${CMAKE_SOURCE_DIR})
message(STATUS "Engine Folder: ${CMAKE_SOURCE_DIR}/engine")
message(STATUS "Source Folder: ${PROJECT_SOURCE_DIR} ")
set_target_properties(application PROPERTIES
    CXX_STANDARD 17
    LIBRARY_DIRECTORY ${CMAKE_SOURCE_DIR}/libraries
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)

# copy SDL binaries
get_target_property(runtime_folder application RUNTIME_OUTPUT_DIRECTORY_DEBUG)
get_target_property(library_directory application LIBRARY_DIRECTORY)

if(DEFINED WITH_SDL AND WITH_SDL)
    add_custom_command(
        TARGET application POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_BIN}/ ${runtime_folder}/
        COMMENT "Copy SDL3 dynamic binaries")

    add_custom_command(
        TARGET application POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_image_BIN}/ ${runtime_folder}/
        COMMENT "Copy SDL3_image dynamic binaries")
endif()

add_custom_command(
    TARGET application POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${runtime_folder}/assets
    COMMENT "Copy assets")
