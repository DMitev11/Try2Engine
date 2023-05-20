#pragma once
#include <vector>
#include <SDL3/SDL.h>
#include "sdl_renderer_object.h" 
namespace render {
    namespace sdl {
        static objects::Renderer createRenderer(SDL_Window* window, const char* driverName, std::vector<uint32_t> initFlags);
        static void setDrawColor(objects::SDLRenderer renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    };
}