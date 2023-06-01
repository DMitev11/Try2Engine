#pragma once

#include <vector>

#include "object.h"
#include "sdl_window.h"
namespace window {
    template <typename... Args>
    static objects::Window *CreateWindow(Args...);
}; // namespace window

#ifdef SDL_USED
#include <SDL3/SDL.h>
template <typename... Args>
inline static objects::Window *
window::CreateWindow(Args... args) {
    return sdl::CreateWindow(args...);
}

#endif