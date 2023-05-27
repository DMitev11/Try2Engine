#pragma once

#include <vector>

#include "window_object.h"
namespace window
{
    template <typename... Args>
    static objects::Window *
    CreateWindow(Args...);
}; // namespace window

#ifdef SDL_USED
#include "sdl_window.h"
#include "sdl_window_object.h"
#include <SDL3/SDL.h>
template <typename... Args>
inline static objects::Window *
window::CreateWindow(Args... args)
{
    return sdl::CreateWindow(args...);
}

#endif