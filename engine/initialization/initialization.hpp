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
    init(Args... args);
    extern const std::vector<uint32_t> DEFAULT_INIT_FLAGS;
    extern const std::unordered_map<const char *, const char *> DEFAULT_HINTS;

}; // namespace initialization

#ifdef SDL_USED
#include "sdl_initialization.h"
const std::vector<uint32_t> initialization::DEFAULT_INIT_FLAGS = std::vector<uint32_t>{32};
const std::unordered_map<const char *, const char *> initialization::DEFAULT_HINTS = {{"SDL_HINT_RENDER_SCALE_QUALITY", "1"}};
template <typename... Args>
inline bool
initialization::init(Args... args)
{
    printf("SDL Initialization");
    return sdl::init(args...);
}
#endif
