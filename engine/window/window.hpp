#pragma once

#include <vector>

#include "sdl_window.h"
#include <objects/object.h>
namespace window {
    template <typename... Args>
    inline static bool init(Args...);
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
    static objects::Window *createWindow(Args...);

    template <typename... Args>
    static void terminate(Args...);

    template <typename... Args>
    static void shutdown(Args...);
}; // namespace window

#ifdef SDL_USED
#include <SDL3/SDL.h>
template <typename... Args>
inline static bool window::init(Args... args) {
    return sdl::init(args...);
}
template <typename... Args>
inline static objects::Window *
window::createWindow(Args... args) {
    return sdl::createWindow(args...);
}
template <typename... Args>
inline static void window::terminate(Args... args) {
    return sdl::terminate(args...);
}
template <typename... Args>
inline static void window::shutdown(Args... args) {
    return sdl::shutdown(args...);
}

#endif