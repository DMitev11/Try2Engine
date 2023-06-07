#pragma once
#include <iostream>
#include <unordered_map>
namespace initialization {
    template <typename... Args>
    static bool init(Args... args);
}; // namespace initialization

#ifdef SDL_USED
#include "sdl_initialization.h"
#include <SDL3/SDL.h>
template <typename... Args>
inline bool initialization::init(Args... args) {
    ("SDL Initialization");
    return sdl::init(args...);
}
#endif
