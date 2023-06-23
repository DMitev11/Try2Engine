
cmake_minimum_required(VERSION 3.15)
project(Try2Engine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

# Default Flags
set(WITH_SDL TRUE)
set(WITH_IMGUI TRUE)
set(WITH_STB TRUE)
set(WITH_BOX2D TRUE)
set(WITH_TESTS TRUE)

set(CMAKE_BINARY_DIR ./build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
message(STATUS "WITH_SDL ${WITH_SDL}")
message(STATUS "WITH_IMGUI ${WITH_IMGUI}")
message(STATUS "WITH_SDL_IMAGE ${WITH_SDL_IMAGE}")
message(STATUS "WITH_STB ${WITH_STB}")
message(STATUS "WITH_BOX2D ${WITH_BOX2D}")
message(STATUS "WITH_TESTS ${WITH_TESTS}")
set_property(GLOBAL PROPERTY USE_FOLDERS ON) # ??

set(CMAKE_INSTALL_LIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")
set(ENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/engine")

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    include(windows_config.cmake)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
    include(linux_config.cmake)
endif()

include(modules_config.cmake)
set(SPDLOG_INCLUDE_DIRS "${ENGINE_ROOT}/libraries/spdlog/include")

# # Add source to this project's executable.
# # TODO: Add tests and install targets if needed.
add_subdirectory("./engine")

add_subdirectory("./try1")

if(DEFINED WITH_TESTS AND WITH_TESTS AND CMAKE_VERSION VERSION_GREATER_EQUAL "3.26")
    message(STATUS "Tests are built")
    set(BUILD_TESTS TRUE)
elseif(DEFINED WITH_TESTS AND WITH_TESTS AND CMAKE_VERSION VERSION_LESS "3.26")
    message(STATUS "Cannot build tests due to a too low CMake version")
    set(BUILD_TESTS FALSE)
endif()

if(DEFINED BUILD_TESTS AND BUILD_TESTS)
    add_subdirectory("./tests")
endif()

if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT try1)
endif()