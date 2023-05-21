#pragma once
#include "sdl_renderer_object.h"
#include <SDL3/SDL.h>
#include <vector>
namespace render
{
    namespace sdl
    {
        extern objects::Renderer
        createRenderer(SDL_Window *window, const char *driverName, std::vector<uint32_t> initFlags);
        extern void
        setDrawColor(objects::SDLRenderer renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    }; // namespace sdl
} // namespace render