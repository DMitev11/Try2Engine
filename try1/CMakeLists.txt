cmake_minimum_required(VERSION 3.15)

# Set project name
project(Try1 LANGUAGES CXX)

set(HEADER_FILES
    inc/Try1.h
    inc/GameLayer.h
)
set(SOURCE_FILES
    main.cpp
    src/GameLayer.cpp
    src/Try1.cpp)
add_executable(try1 ${SOURCE_FILES})

target_compile_features(try1 PUBLIC cxx_std_17)
target_link_libraries(try1 PUBLIC imgui utils window render loader logger input gui box2d::box2d)
target_include_directories(try1 PUBLIC ${ENGINE_ROOT} ${CMAKE_CURRENT_SOURCE_DIR}/ ${box2d_INCLUDE_DIRS})

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
    if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        add_custom_command(
            TARGET try1 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_BIN}/ ${runtime_folder}/
            COMMENT "Copy SDL3 dynamic binaries")

        if(DEFINED WITH_SDL_IMAGE AND WITH_SDL_IMAGE)
            add_custom_command(
                TARGET try1 POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_image_BIN}/ ${runtime_folder}/
                COMMENT "Copy SDL3_image dynamic binaries")
        endif()
    endif()
endif()

add_custom_command(
    TARGET try1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${runtime_folder}/assets
    COMMENT "Copy assets")
