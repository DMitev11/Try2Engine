#pragma once
#include <iostream>
#include <vector>
#include <unordered_map> 
namespace initialization
{
    template <typename... Args>
    static bool init(Args... args);

#ifdef SDL_USED
#include <SDL3/SDL.h>
    const std::vector<uint32_t> DEFAULT_INIT_FLAGS = { 32 };
    const std::unordered_map<const char*, const char*> DEFAULT_HINTS = { {"SDL_HINT_RENDER_SCALE_QUALITY", "1"} };

#endif
};

#ifdef SDL_USED
#include "sdl_initialization.h"
template <typename... Args>
inline bool initialization::init(Args... args)
{
    printf("SDL Initialization");
    return sdl::init(args...);
}
#endif
