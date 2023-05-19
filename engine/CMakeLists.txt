
cmake_minimum_required(VERSION 3.12)
project(engine LANGUAGES CXX)

# Add a custom path to the CMAKE_PREFIX_PATH variable
add_subdirectory(./initialization)
add_subdirectory(./window)