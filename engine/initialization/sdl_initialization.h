#pragma once
#include <unordered_map>
#include <vector>
namespace initialization
{
    namespace sdl
    {
        extern bool
        init(std::vector<uint32_t> initFlags, std::unordered_map<const char *, const char *> hintFlags);
    };
}; // namespace initialization

// namespace initialization
//   // Initialize PNG loading
//             int imgFlags = IMG_INIT_PNG;
//             if (!(IMG_Init(imgFlags) & imgFlags))
//             {
//                 printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
//                 success = false;
//             }
