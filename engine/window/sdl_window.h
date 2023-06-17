#pragma once
#include <vector>

#include <SDL3/SDL.h>
#include <sdl_window_object.h>
#include <unordered_map>
#include <window_object.h>
namespace window {
    /**
     * @brief Implementation based on namespace window
     * public facade
     *
     */
    namespace sdl {
        /**
         * @brief Default flags to initialize window
         * creation logic.
         * Defaults are based on what's only necessary to
         * create a window.
         * @note Each flag represents a different part of
         * SDL which can be utilized. `SDL_INIT_VIDEO` is
         * the default flag for window creation
         * @see SDL_init.h#SDL_InitFlags
         *
         */
        const std::vector<uint32_t> kDefaultInitFlags = {
            SDL_INIT_VIDEO};

        /**
         * @brief Default hints to intialize window creation
         * logic with. Each hints represents a different
         * setting in SDL
         *
         * @see SDL_hints.h
         *
         */
        const std::unordered_map<const char *, const char *>
            kDefaulInitHints = {
                {"SDL_HINT_RENDER_SCALE_QUALITY", "1"},
                {"SDL_HINT_FRAMEBUFFER_ACCELERATION", "1"}};

        /**
         * @brief Initialize window creation logic.
         * Initialize `flags` (/ref kDefaultInitFlags) and
         * set hints(although not necessary)
         * @note SDL3 does not require initialization but
         * SDL2 does. Recommended calling it for consistency
         * in external code and easy translation between
         * different external libraries
         *
         * @param initFlags to initialize
         * @param hintFlags to set
         * @return true: Successful initializaiton \n false:
         * Unsuccessful initialization - look into logger
         * emitted messages for further info
         */
        extern bool
        init(std::vector<uint32_t> initFlags =
                 kDefaultInitFlags,
             std::unordered_map<const char *, const char *>
                 hintFlags = kDefaulInitHints);

        /**
         * @brief Create a Window object using SDL
         * @see sdl_window_object.h
         * @warning Call sdl::init first
         *
         * @param height in natural numbers
         * @param width in natural numbers
         * @param title displayed in navbar
         * @param flags specific for this window. Each flag
         * represents an enabled behaviour
         * @see SDL_video.h#SDL_WindowFlags
         *
         * @return objects::Window* used in other parts of
         * the engine
         */
        extern objects::Window *
        createWindow(int height, int width,
                     const char *title,
                     std::vector<uint32_t> flags = {
                         SDL_WINDOW_RESIZABLE,
                         SDL_WINDOW_INPUT_FOCUS});

        /**
         * @brief Close a window, and cleanup after that
         *
         * @param window Window to terminate
         */
        extern void terminate(objects::Window *window);

        /**
         * @see sdl::terminate
         */
        extern void terminate(SDL_Window *window);

        /**
         * @brief Shutdown SDL3's window creation logic
         * initialized previously
         * @see sdl::init
         *
         * @param initFlags Each flag represents a part of
         * SDL to be shutdown
         */
        extern void
        shutdown(std::vector<uint32_t> initFlags =
                     kDefaultInitFlags);
    } // namespace sdl
};    // namespace window
