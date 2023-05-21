#pragma once
#include <SDL3/SDL.h>

#include <vector>

#include "window_object.h"
namespace window
{
    template <typename... Args>
    static objects::Window
    createWindow(Args...);

    extern const std::vector<uint32_t> DEFAULT_WINDOW_INIT_FLAGS;
    extern const std::vector<uint32_t> DEFAULT_RENDERER_INIT_FLAGS;
#ifdef SDL_USED

#endif
}; // namespace window

#ifdef SDL_USED
#include "sdl_window.h"
const std::vector<uint32_t> window::DEFAULT_WINDOW_INIT_FLAGS = {0x00000020, 0x00004000};
const std::vector<uint32_t> window::DEFAULT_RENDERER_INIT_FLAGS = {0x00000002};
template <typename... Args>
inline static objects::Window
window::createWindow(Args... args)
{
    return sdl::createWindow(args...);
}

#endif