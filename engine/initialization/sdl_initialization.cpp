#include "sdl_initialization.h"
#include <SDL3/SDL.h>
#include <SDL_image.h>
using namespace initialization;
bool
sdl::Init(std::vector<uint32_t> initFlags, std::unordered_map<const char *, const char *> initHints, std::vector<uint32_t> imgFlags)
{
    uint32_t flags = 0;
    for each (uint32_t flag in initFlags)
    {
        flags = flags | flag;
    }
    // Initialize SDL
    if (SDL_Init(flags) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    std::vector<const char *> keys;
    keys.reserve(initHints.size());

    for (auto kv : initHints)
    {
        keys.push_back(kv.first);
    }
    for (int i = 0; i < keys.size(); i++)
    {
        if (!SDL_SetHint(keys.at(i), initHints.at(keys.at(i))))
        {
            printf("Warning: Linear texture filtering not enabled!");
            return false;
        }
    }

    int imgInitFlags = 0;
    for each (int flag in imgFlags)
    {
        imgInitFlags = imgInitFlags | flag;
    }
    if (!(IMG_Init(imgInitFlags) & imgInitFlags))
    {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}