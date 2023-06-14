cmake_minimum_required(VERSION 3.13)

set(HEADER_FILES
    core/gui_layer.h
    core/gui_widget.h
    widgets/example_widget.h
)

set(SOURCE_FILES
    core/gui_layer.cpp
    widgets/example_widget.cpp
)

add_library(gui STATIC ${HEADER_FILES} ${SOURCE_FILES})

# @todo add raise condition if IMGUI is actually used
target_link_libraries(gui PUBLIC imgui utils)
target_include_directories(gui PUBLIC ${LIBRARY_OBJECTS_INCLUDE} ${IMGUI_DIR})

set_target_properties(gui PROPERTIES
    LINKER_LANGUAGE CXX
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_SOURCE_DIR}/build/debug
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_SOURCE_DIR}/build/release
)