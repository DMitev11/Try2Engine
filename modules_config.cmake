if(DEFINED WITH_SDL AND WITH_SDL)
    find_package(SDL3 REQUIRED)

    if(DEFINED WITH_SDL_IMAGE AND WITH_SDL_IMAGE)
        find_package(SDL3_image REQUIRED)
    elseif(NOT WITH_SDL_IMAGE AND NOT WITH_STB)
        MESSAGE(FATAL_ERROR "Define -DWITH_SDL_IMAGE or -DWITH_STB (-DWITH_STB for linux)")
    else()
    endif()
endif()

set(IMGUI_DIR
    ${ENGINE_ROOT}/libraries/imgui
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
    target_compile_definitions(imgui PUBLIC USE_SDL)
    target_include_directories(imgui PUBLIC ${SDL3_INCLUDE_DIRS})
    target_link_libraries(imgui PUBLIC ${SDL3_LIBRARIES})
endif()

find_package(box2d REQUIRED)