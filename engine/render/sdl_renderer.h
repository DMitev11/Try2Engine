#pragma once

#include <renderer_object.h>
#include <texture_object.h>
#include <window_object.h>
#include <SDL3/SDL.h>
#include <vector>
namespace render
{
    namespace sdl
    {
        const std::vector<uint32_t> kRendererInitFlags = { SDL_RENDERER_ACCELERATED };
        extern objects::Renderer*
            CreateRenderer(objects::Window* window, const char* driverName = 0, std::vector<uint32_t> initFlags = kRendererInitFlags);
        extern objects::Renderer*
            CreateRenderer(SDL_Window* window, const char* driverName = 0, std::vector<uint32_t> initFlags = kRendererInitFlags);
        extern void
            SetDrawColor(objects::Renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        extern void
            SetDrawColor(SDL_Renderer* renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        extern void
            RenderAsset(objects::Renderer* renderer, objects::Texture* texture, float x, float y);
        extern void
            RenderAsset(SDL_Renderer* renderer, SDL_Texture* texture, float w, float h, float x, float y);
        extern void
            ClearRender(objects::Renderer* renderer);
        extern void
            ClearRender(SDL_Renderer* renderer);
        extern void
            RenderFrame(objects::Renderer* renderer);
        extern void
            RenderFrame(SDL_Renderer* renderer);

    }; // namespace sdl
} // namespace render