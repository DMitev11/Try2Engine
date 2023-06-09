#include "./sdl_window.h"
#include <logger/logger.h>
#include <sdl_window_object.h>
#include <stdexcept>
using namespace window;
objects::Window*
sdl::createWindow(int height, int width, const char* title,
    std::vector<uint32_t> flags) {
    // Combine all flags
    uint32_t flagsOr = 0;
    for each (uint32_t flag in flags) {
        flagsOr = flagsOr | flag;
    }
    // Create window
    SDL_Window* window =
        SDL_CreateWindow(title, width, height, flagsOr);
    if (window == NULL) {
        LOG_ENGINE_ERROR(
            "Could not render texture! SDL Error:",
            SDL_GetError());
        return nullptr;
    }
    return new objects::SDLWindow(window, height, width,
        title);
}
