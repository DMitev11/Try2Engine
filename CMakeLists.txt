# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.12)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Try2Engine LANGUAGES CXX VERSION 0.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) # ??

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
set(ENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/engine")
set(SDL3_DIR "${ENGINE_ROOT}/libraries/SDL/install/cmake")
set(SDL3_INCLUDE_DIRS "${ENGINE_ROOT}/libraries/SDL/install/include")
set(SDL3_BIN "${ENGINE_ROOT}/libraries/SDL/install/bin")
set(SDL3_image_DIR "${ENGINE_ROOT}/libraries/SDL_Image/install/cmake")
set(SDLIMAGE_INCLUDE_DIR "${ENGINE_ROOT}/libraries/SDL_Image/install/include")
set(SDL3_image_BIN "${ENGINE_ROOT}/libraries/SDL_Image/install/bin")

# Add source to this project's executable.
# TODO: Add tests and install targets if needed.
add_subdirectory("./engine")
add_subdirectory("./application")

# install(
# TARGETS engine
# RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
# ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
# LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )
# include(FetchContent)
# FetchContent_Declare(
# googletest
# GIT_REPOSITORY https://github.com/google/googletest.git
# GIT_TAG        58d77fa8070e8cec2dc1ed015d66b454c8d78850 # release-1.10.0
# )
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# FetchContent_MakeAvailable(googletest)
