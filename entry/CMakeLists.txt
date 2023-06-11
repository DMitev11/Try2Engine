cmake_minimum_required(VERSION 3.12)

# Set project name
project(Entry LANGUAGES CXX)

set(HEADER_FILES
)
set(SOURCE_FILES
    main.cpp)
add_library(entry SHARED IMPORTED ${SOURCE_FILES})
add_library(entry_lib STATIC ${SOURCE_FILES})

set_target_properties(entry_lib PROPERTIES
    OUTPUT_NAME entry
)

target_compile_features(entry_lib PUBLIC cxx_std_17)
target_link_libraries(entry_lib PUBLIC window render loader logger input)
target_include_directories(entry_lib PUBLIC ${ENGINE_ROOT} ${CMAKE_CURRENT_SOURCE_DIR}/)

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(entry_lib PUBLIC SDL_USED)
    find_package(SDL3 REQUIRED)
    find_package(SDL3_image REQUIRED)
    target_include_directories(entry_lib PUBLIC ${SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR} ${SPDLOG_INCLUDE_DIRS}/)
    target_link_libraries(entry_lib PUBLIC ${SDL3_LIBRARIES} SDL3_image::SDL3_image)
endif()

message(STATUS "Engine Folder: ${CMAKE_SOURCE_DIR}/engine")
message(STATUS "Source Folder: ${PROJECT_SOURCE_DIR} ")
set_target_properties(entry_lib PROPERTIES
    CXX_STANDARD 17
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)
