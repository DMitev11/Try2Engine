
cmake_minimum_required(VERSION 3.15)
project(Try2Engine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "WITH_SDL ${WITH_SDL}")
message(STATUS "WITH_IMGUI ${WITH_IMGUI}")
message(STATUS "WITH_SDL_IMAGE ${WITH_SDL_IMAGE}")
message(STATUS "WITH_STB ${WITH_STB}")
message(STATUS "WITH_BOX2D ${WITH_BOX2D}")
message(STATUS "BUILD_TESTS ${BUILD_TESTS}")
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
