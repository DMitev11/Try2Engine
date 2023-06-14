cmake_minimum_required(VERSION 3.26)
set(IMGUI_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui
)
set(IMGUI_SOURCE
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_draw.cpp)

if(DEFINED WITH_SDL AND WITH_SDL)
    set(IMGUI_SOURCE
        ${IMGUI_SOURCE}
        ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp)
endif()

add_library(imgui STATIC ${IMGUI_SOURCE})
target_include_directories(imgui PUBLIC ${IMGUI_DIR}/)

if(DEFINED WITH_SDL AND WITH_SDL)
    target_compile_definitions(imgui PUBLIC SDL_USED)
    target_include_directories(imgui PUBLIC {SDL3_INCLUDE_DIRS} ${SDLIMAGE_INCLUDE_DIR})
    find_package(SDL3 REQUIRED)
    target_link_libraries(imgui PUBLIC ${SDL3_LIBRARIES})
endif()