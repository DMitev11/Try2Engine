#include "./sdl_window.h"
#include "sdl_window_object.h"
#include <stdexcept>
using namespace window;
objects::Window *
sdl::createWindow(int height, int width, const char *title,
                  std::vector<uint32_t> flags) {
    // Create window
    uint32_t flagsOr = 0;
    for each (uint32_t flag in flags) {
        flagsOr = flagsOr | flag;
    }
    SDL_Window *window =
        SDL_CreateWindow(title, width, height, flagsOr);
    if (window == NULL) {
        std::string err =
            ("Window could not be created! SDL Error: %s\n",
             SDL_GetError());
        throw std::runtime_error(err);
    }
    return new objects::SDLWindow(window, height, width,
                                  title);
}
