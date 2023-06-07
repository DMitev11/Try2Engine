#include "sdl_initialization.h"
#include "logger/logger.h"
#include <SDL3/SDL.h>
#include <SDL_image.h>
using namespace initialization;
bool sdl::init(
    std::vector<uint32_t> initFlags,
    std::unordered_map<const char *, const char *>
        initHints,
    std::vector<uint32_t> imgFlags) {
    uint32_t flags = 0;
    for each (uint32_t flag in initFlags) {
        flags = flags | flag;
    }
    // Initialize SDL
    if (SDL_Init(flags) < 0) {
        LOG_ENGINE_ERROR(
            "SDL could not initialize! SDL Error: ",
            SDL_GetError());
        return false;
    }

    std::vector<const char *> keys;
    keys.reserve(initHints.size());

    for (auto kv : initHints) {
        keys.push_back(kv.first);
    }
    for (int i = 0; i < keys.size(); i++) {
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

    int imgInitFlags = 0;
    for each (int flag in imgFlags) {
        imgInitFlags = imgInitFlags | flag;
    }
    if (!(IMG_Init(imgInitFlags) & imgInitFlags)) {
        LOG_ENGINE_ERROR(
            "SDL_image could not initialize! SDL_image "
            "Error: ",
            IMG_GetError());
        return false;
    }
    return true;
}