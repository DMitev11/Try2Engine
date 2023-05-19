#pragma once
#include <vector>
#include <unordered_map>
    #ifdef SDL_USED 
    #include "sdl_initialization.h"
    #include <SDL3/SDL.h>
    #endif
class Initialization
{
public:
 
    static const std::vector<uint32_t> DEFAULT_INIT_FLGAS;
    static const std::unordered_map<const char*, const char*> DEFAULT_HINTS;

    template <typename... Args>
    static bool init(Args... args)
    {
        #ifdef SDL_USED 
        return SDLInitialization::init(args...);
        #endif
    }
};

#ifdef SDL_USED 
const std::vector<uint32_t> Initialization::DEFAULT_INIT_FLGAS = {32};
const std::unordered_map<const char*, const char*> Initialization::DEFAULT_HINTS = {{"SDL_HINT_RENDER_SCALE_QUALITY", "1"}};
#endif
   