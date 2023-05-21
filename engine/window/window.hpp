#pragma once
#include <SDL3/SDL.h>

#include <vector>

#include "sdl_window_object.h"
#include "window_object.h"
namespace window
{
    template <typename... Args>
    static objects::SDLWindow *
    CreateWindow(Args...);

#ifdef SDL_USED

#endif
}; // namespace window

#ifdef SDL_USED
#include "sdl_window.h"
template <typename... Args>
inline static objects::SDLWindow *
window::CreateWindow(Args... args)
{
    return sdl::CreateWindow(args...);
}

#endif