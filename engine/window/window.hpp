#pragma once
#include <vector>
#include "window_object.h"
namespace window
{
    template<typename... Args>
    static objects::Window createWindow(Args...);

#ifdef SDL_USED
#include <SDL3/SDL.h>
    const std::vector<uint32_t> DEFAULT_WINDOW_INIT_FLAGS = { SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE };
    const std::vector<uint32_t> DEFAULT_RENDERER_INIT_FLAGS = { SDL_RENDERER_ACCELERATED };

#endif
};

#ifdef SDL_USED
#include "./sdl_window.h"
template<typename... Args>
inline static objects::Window window::createWindow(Args... args) {
    return sdl::createWindow(args...);
}

#endif