#include "./sdl_initialization.h"
#include <SDL3/SDL.h>

bool SDLInitialization::init(std::vector<uint32_t> initFlags, std::unordered_map<const char*, const char*> hintFlags)
{
    bool success = true;
    uint32_t flags = 0;
    for each(uint32_t flag in initFlags) { 
        flags = flags | flag;
    } 
    if (SDL_Init(flags) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    std::vector<const char*> keys;
    keys.reserve(hintFlags.size()); 

    for(auto kv : hintFlags) {
        keys.push_back(kv.first); 
    } 
    for(int i = 0; i < keys.size();i++) { 
        if (!SDL_SetHint(keys.at(i), hintFlags.at(keys.at(i))))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }
    }
    return success;
}
