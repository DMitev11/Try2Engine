#pragma once

#include <vector>

#include "object.h"
#include "sdl_window.h"
namespace window {
    template <typename... Args>
    static objects::Window *createWindow(Args...);
}; // namespace window

#ifdef SDL_USED
#include <SDL3/SDL.h>
template <typename... Args>
inline static objects::Window *
window::createWindow(Args... args) {
    return sdl::createWindow(args...);
}

#endif