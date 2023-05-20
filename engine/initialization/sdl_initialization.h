#pragma once
#include <vector>
#include <unordered_map> 
namespace initialization {
    namespace sdl {
        static bool init(std::vector<uint32_t> initFlags, std::unordered_map<const char*, const char*> hintFlags);
    };
};
//   // Initialize PNG loading
//             int imgFlags = IMG_INIT_PNG;
//             if (!(IMG_Init(imgFlags) & imgFlags))
//             {
//                 printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
//                 success = false;
//             }
