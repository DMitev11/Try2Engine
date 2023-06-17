#pragma once

#include <vector>
#include <window_object.h>

/**
 * @brief Window interactions. \n Initialize or shutdown
 * window library/libraries. \n Create or terminate a
 * window, based on ext. libraries
 * @note Facade
 *
 */
namespace window {
    /**
     * @brief Initialize all required libraries to create a
     * window.
     *
     * @tparam Args Variations of flags used during
     * initalizaiton, based on the library used to create a
     * window
     * @return true: Sucessful - does not
     * emit any logger messages. \n false: Unsuccessful -
     * log errors are emitted for more information.
     */
    template <typename... Args>
    inline static bool init(Args...);
    /**
     * @brief Create a Window object. , later used to hook a
     * renderer to, interrupt mouse/keyboard input and more
     *
     * @tparam variadic, depends on the package used for
     * window creation
     * @return objects::Window* on success, nullptr
     * on fail (should emit an error message in the logger)
     *
     * @see objects::Window
     */
    template <typename... Args>
    static objects::Window *createWindow(Args...);

    /**
     * @brief Terminate a window
     *
     * @param window Window object to be terminated.
     */
    static void terminate(objects::Window *window);

    /**
     * @brief Shutdown window library/libraries.
     * @warning Do not call until last frame of the
     * application - could lead to unhandled exceptions and
     * undefined behaviour
     *
     * @tparam Args Flags and settings to be cleaned-up
     * before closing
     */
    template <typename... Args>
    static void shutdown(Args...);
}; // namespace window

/**
 * @brief Call SDL-dependent implementations of this facade
 *
 */
#ifdef USE_SDL
#include "sdl_window.h"
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

inline static void
window::terminate(objects::Window *window) {
    return sdl::terminate(window);
}
template <typename... Args>
inline static void window::shutdown(Args... args) {
    return sdl::shutdown(args...);
}

#endif