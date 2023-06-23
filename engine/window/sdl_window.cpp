#include "./sdl_window.h"
#include <SDL3/SDL.h>
#include <logger/logger.h>
#include <objects/helpers_object.hpp>
#include <sdl_window_object.h>
#include <stdexcept>
using namespace window;

bool sdl::init(
    std::vector<uint32_t> initFlags,
    std::unordered_map<const char *, const char *>
        initHints) {

    // As of SDL's implementation, each flag should be OR'ed
    // with the rest into an unsigned 32 bit integer
    uint32_t flags = 0;
    for (int i = 0; i < initFlags.size(); i++) {
        // Initialize the flag if necessary
        if (initFlags[i] != SDL_WasInit(initFlags[i])) {
            flags |= initFlags[i];
        }
    }
    // Initialize SDL
    if (SDL_Init(flags) < 0) {
        LOG_ENGINE_ERROR(
            "SDL could not initialize! SDL Error: ",
            SDL_GetError());
        return false;
    }

    // Retrieve all argumented hints and set them one by one
    std::vector<const char *> keys;
    keys.reserve(initHints.size());

    for (auto kv : initHints) {
        keys.push_back(kv.first);
    }
    for (int i = 0; i < keys.size(); i++) {
        if (SDL_GetHint(keys.at(i)) !=
            initHints.at(keys.at(i))) {
            if (!SDL_SetHint(keys.at(i),
                             initHints.at(keys.at(i)))) {
                LOG_ENGINE_ERROR(
                    ""
                    "Warning: Linear texture filtering not "
                    "enabled!",
                    SDL_GetError());
                return false;
            }
        }
    }
    return true;
}

objects::Window *
sdl::createWindow(int height, int width, const char *title,
                  std::vector<uint32_t> flags) {

    // As of SDL's implementation, each flag should be OR'ed
    // with the rest into an unsigned 32 bit integer
    uint32_t flagsOr = 0;
    for (int i = 0; i < flags.size(); i++) {
        flagsOr |= flags[i];
    }
    // Create window
    SDL_Window *window =
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

void sdl::terminate(objects::Window *window) {
    return sdl::terminate(objects::toSdlWindow(window));
}

void sdl::terminate(SDL_Window *window) {
    SDL_DestroyWindow(window);
    auto err = SDL_GetError();
    if (err != "") {
        LOG_ENGINE_ERROR("Window: ", err);
    }
    return;
}

void sdl::shutdown(std::vector<uint32_t> initFlags) {
    uint32_t flags = 0;
    for (int i = 0; i < initFlags.size(); i++) {
        // Check if the flag have been initialized
        // SDL_WasInit(<flag>) returns <flag> value if
        // initialized
        if (initFlags[i] == SDL_WasInit(initFlags[i])) {
            flags |= initFlags[i];
        }
    }
    SDL_QuitSubSystem(flags);
}
