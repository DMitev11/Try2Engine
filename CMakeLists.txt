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
set(SDL3_BIN "${ENGINE_ROOT}/libraries/SDL/install/bin")
set(SDL3_image_DIR "${ENGINE_ROOT}/libraries/SDL_Image/install/cmake")
set(SDL3_image_BIN "${ENGINE_ROOT}/libraries/SDL_Image/install/bin")
set(EASTL_ROOT_DIR ${ENGINE_ROOT}/libraries/EASTL)
include_directories (${EASTL_ROOT_DIR}/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAAssert/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EABase/include/Common)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAMain/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAStdC/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EATest/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAThread/include)
set(EASTL_LIBRARY debug ${EASTL_ROOT_DIR}/build/Debug/EASTL.lib optimized ${EASTL_ROOT_DIR}/build/Release/EASTL.lib)
add_custom_target(NatVis SOURCES ${EASTL_ROOT_DIR}/doc/EASTL.natvis)

# add_subdirectory("./application")
# add_subdirectory("./libraries")
# Add source to this project's executable.
# TODO: Add tests and install targets if needed.
add_compile_definitions(SDL_USED)
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
