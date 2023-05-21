#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#ifdef SDL_USED
#include <SDL3/SDL.h>
#endif
namespace initialization
{
    template <typename... Args>
    static bool
    Init(Args... args);
}; // namespace initialization

#ifdef SDL_USED
#include "sdl_initialization.h"
template <typename... Args>
inline bool
initialization::Init(Args... args)
{
    printf("SDL Initialization");
    return sdl::Init(args...);
}
#endif
