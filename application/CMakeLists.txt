cmake_minimum_required(VERSION 3.12)

# Set project name
project(Application LANGUAGES CXX C)

add_executable(application ./main.cpp)

target_link_libraries(application PRIVATE window)
target_include_directories(application PUBLIC ${CMAKE_SOURCE_DIR}/engine)

message(STATUS "Engine Folder: ${CMAKE_SOURCE_DIR}/engine")
message(STATUS "Source Folder: ${PROJECT_SOURCE_DIR} ")
set_target_properties(application PROPERTIES
    LIBRARY_DIRECTORY ${CMAKE_SOURCE_DIR}/libraries
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)

# copy SDL binaries
get_target_property(runtime_folder application RUNTIME_OUTPUT_DIRECTORY_DEBUG)
get_target_property(library_directory application LIBRARY_DIRECTORY)
add_custom_command(
    TARGET application POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_BIN}/ ${runtime_folder}/
    COMMENT "Copy SDL3 dynamic binaries")

add_custom_command(
    TARGET application POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_image_BIN}/ ${runtime_folder}/
    COMMENT "Copy SDL3_image dynamic binaries")
