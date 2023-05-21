#pragma once
#include "sdl_renderer_object.h"
#include "window_object.h"
#include <SDL3/SDL.h>
#include <vector>
namespace render
{
    namespace sdl
    {
        const std::vector<uint32_t> kRendererInitFlags = {0x00000002};
        extern objects::Renderer *
        CreateRenderer(objects::Window *window, const char *driverName = 0, std::vector<uint32_t> initFlags = kRendererInitFlags);
        extern objects::Renderer *
        CreateRenderer(SDL_Window *window, const char *driverName = 0, std::vector<uint32_t> initFlags = kRendererInitFlags);
        extern void
        SetDrawColor(objects::Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        extern void
        SetDrawColor(SDL_Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    }; // namespace sdl
} // namespace render