#pragma once
#include <vector>

#include <SDL3/SDL.h>
#include <objects/sdl_window_object.h>
#include <objects/window_object.h>
#include <unordered_map>
namespace window {
    namespace sdl {

        const std::vector<uint32_t> kDefaultInitFlags = {
            SDL_INIT_VIDEO};
        // SDL3 initializes all flags autonomously, without
        // the necessity to call initialization
        extern bool
        init(std::vector<uint32_t> initFlags =
                 kDefaultInitFlags,
             std::unordered_map<const char *, const char *>
                 hintFlags = {
                     {"SDL_HINT_RENDER_SCALE_QUALITY",
                      "1"}});
        extern objects::Window *
        createWindow(int height, int width,
                     const char *title,
                     std::vector<uint32_t> flags = {
                         SDL_WINDOW_RESIZABLE,
                         SDL_WINDOW_INPUT_FOCUS});

        extern void terminate(objects::Window *window);
        extern void terminate(SDL_Window *window);
        extern void
        shutdown(std::vector<uint32_t> initFlags =
                     kDefaultInitFlags);
    } // namespace sdl
};    // namespace window
