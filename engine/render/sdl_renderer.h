#pragma once

#include <SDL3/SDL.h>
#include <renderer_object.h>
#include <texture_object.h>
#include <vector>
#include <window_object.h>

#ifdef USE_SDL_IMAGE
#include <SDL_image.h>
#endif
namespace render {
    namespace sdl {
        const std::vector<uint32_t> kDefaultInitFlags = {
            SDL_INIT_VIDEO};

#ifdef USE_SDL_IMAGE
        extern bool
        init(std::vector<uint32_t> initFlags =
                 kDefaultInitFlags,
             std::vector<uint32_t> imageInitFlags = {
                 IMG_INIT_JPG, IMG_INIT_PNG});
#else
        extern bool init(std::vector<uint32_t> initFlags =
                             kDefaultInitFlags);
#endif
        extern objects::Renderer *
        CreateRenderer(objects::Window *window,
                       const char *driverName = 0,
                       std::vector<uint32_t> initFlags = {
                           SDL_RENDERER_ACCELERATED});
        extern objects::Renderer *
        CreateRenderer(SDL_Window *window,
                       const char *driverName = 0,
                       std::vector<uint32_t> initFlags = {
                           SDL_RENDERER_ACCELERATED});

        extern void
        SetDrawColor(objects::Renderer *renderer, uint8_t r,
                     uint8_t g, uint8_t b, uint8_t a);
        extern void SetDrawColor(SDL_Renderer *renderer,
                                 uint8_t r, uint8_t g,
                                 uint8_t b, uint8_t a);

        extern void RenderAsset(objects::Renderer *renderer,
                                objects::Texture *texture,
                                float x, float y);
        extern void RenderAsset(SDL_Renderer *renderer,
                                SDL_Texture *texture,
                                float w, float h, float x,
                                float y);

        extern objects::TextureSize
        GetTextureSize(objects::Texture *texture);
        extern objects::TextureSize
        GetTextureSize(SDL_Texture *texture);

        extern void
        ClearRender(objects::Renderer *renderer);
        extern void ClearRender(SDL_Renderer *renderer);

        extern void
        RenderFrame(objects::Renderer *renderer);
        extern void RenderFrame(SDL_Renderer *renderer);

        extern void terminate(objects::Renderer *renderer);
        extern void terminate(SDL_Renderer *renderer);
        extern void
        shutdown(std::vector<uint32_t> initFlags =
                     kDefaultInitFlags);
    }; // namespace sdl
} // namespace render