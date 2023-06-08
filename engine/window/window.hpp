#pragma once

#include <vector>

#include "object.h"
#include "sdl_window.h"
namespace window {
    /**
     * @brief Create a Window object, later used to hook a
     * renderer to, interrupt mouse/keyboard input and more
     *
     * @param args variadic, depends on the package used for
     * window creation
     * @return objects::Window* on success, nullptr
     * on fail (should emit an error message in the logger)
     *
     * @see objects::Window
     */
    template <typename... Args>
    static objects::Window* createWindow(Args...);
}; // namespace window

#ifdef SDL_USED
#include <SDL3/SDL.h>
template <typename... Args>
inline static objects::Window*
window::createWindow(Args... args) {
    return sdl::createWindow(args...);
}

#endif