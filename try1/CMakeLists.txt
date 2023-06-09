cmake_minimum_required(VERSION 3.15)

# Set project name
project(Try1 LANGUAGES CXX)

set(HEADER_FILES
    inc/Try1.h
    inc/GameLayer.h
    inc/GameData.h
    inc/ControllerWidget.h
)
set(SOURCE_FILES
    main.cpp
    src/ControllerWidget.cpp
    src/GameLayer.cpp
    src/Try1.cpp)
add_executable(try1 ${SOURCE_FILES})

target_compile_features(try1 PUBLIC cxx_std_17)
target_link_libraries(try1 PUBLIC imgui utils window render loader logger input gui box2d::box2d)
target_include_directories(try1 PUBLIC ${ENGINE_ROOT} ${CMAKE_CURRENT_SOURCE_DIR}/ ${box2d_INCLUDE_DIRS})

message(STATUS "Engine Folder: ${CMAKE_SOURCE_DIR}/engine")
message(STATUS "Source Folder: ${PROJECT_SOURCE_DIR} ")
set(BUILD_FOLDER ${CMAKE_BINARY_DIR}/buildTarget)
set_target_properties(try1 PROPERTIES
    CXX_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BUILD_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${BUILD_FOLDER}
    RUNTIME_OUTPUT_DIRECTORY ${BUILD_FOLDER}
)

# copy SDL binaries
get_target_property(runtime_debug try1 RUNTIME_OUTPUT_DIRECTORY_DEBUG)
get_target_property(runtime_release try1 RUNTIME_OUTPUT_DIRECTORY_RELEASE)
get_target_property(runtime_generic try1 RUNTIME_OUTPUT_DIRECTORY)

if(DEFINED WITH_SDL AND WITH_SDL)
    if(NOT CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        add_custom_command(
            TARGET try1 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_BIN}/ ${BUILD_FOLDER}/
            COMMENT "Copy SDL3 dynamic binaries")

        if(DEFINED WITH_SDL_IMAGE AND WITH_SDL_IMAGE)
            add_custom_command(
                TARGET try1 POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_directory ${SDL3_image_BIN}/ ${BUILD_FOLDER}/
                COMMENT "Copy SDL3_image dynamic binaries")
        endif()
    endif()
endif()

# There are differences in the build folder based on the platform and OS distributions but I am still figuring out what exactly
add_custom_command(
    TARGET try1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets ${BUILD_FOLDER}/assets
    COMMENT "Copy assets")

message(STATUS ${CMAKE_BUILD_TYPE})