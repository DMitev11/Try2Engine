
cmake_minimum_required(VERSION 3.12)
project(engine LANGUAGES CXX)

# Add a custom path to the CMAKE_PREFIX_PATH variable
set(LIBRARY_OBJECTS_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/objects")
add_subdirectory(${LIBRARY_OBJECTS_INCLUDE})
add_subdirectory(./logger)
add_subdirectory(./window)
add_subdirectory(./render)
add_subdirectory(./loader)
add_subdirectory(./input)
add_subdirectory(./utils)
add_subdirectory(./gui)
add_subdirectory(./libraries)