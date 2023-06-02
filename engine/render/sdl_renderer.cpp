#include "sdl_renderer.h"
#include "helpers_object.hpp"
#include "logger/logger.h"
#include "sdl_renderer_object.h"
#include "sdl_texture_object.h"
#include "sdl_window_object.h"
#include <stdexcept>
#include <vector>
using namespace render;

objects::Renderer *
sdl::CreateRenderer(objects::Window *window,
                    const char *driverName,
                    std::vector<uint32_t> initFlags) {
    return sdl::CreateRenderer(objects::toSdlWindow(window),
                               driverName, initFlags);
}

objects::Renderer *
sdl::CreateRenderer(SDL_Window *window,
                    const char *driverName,
                    std::vector<uint32_t> initFlags) {
    uint32_t flags = 0;
    for each (uint32_t flag in initFlags) {
        flags = flags | flag;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(
        window, SDL_GetHint(SDL_HINT_RENDER_DRIVER), flags);
    if (renderer == NULL) {
        LOG_ENGINE_ERROR(
            "Renderer could not be created! SDL Error:",
            SDL_GetError());
        return nullptr;
    }
    return new objects::SDLRenderer(renderer, window,
                                    driverName, initFlags);
}

void sdl::SetDrawColor(objects::Renderer *renderer,
                       uint8_t r, uint8_t g, uint8_t b,
                       uint8_t a) {
    sdl::SetDrawColor(objects::toSdlRenderer(renderer), r,
                      g, b, a);
}

void sdl::SetDrawColor(SDL_Renderer *renderer, uint8_t r,
                       uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void sdl::RenderAsset(objects::Renderer *renderer,
                      objects::Texture *texture, float x,
                      float y) {
    return sdl::RenderAsset(
        objects::toSdlRenderer(renderer),
        objects::toSdlTexture(texture),
        (float)texture->width, (float)texture->height, x,
        y);
}

void sdl::RenderAsset(SDL_Renderer *renderer,
                      SDL_Texture *texture, float w,
                      float h, float x, float y) {
    SDL_FRect quad = {x, y, w, h};
    int res =
        SDL_RenderTexture(renderer, texture, 0, &quad);
    if (res == -1) {
        LOG_ENGINE_ERROR(
            "Could not render texture! SDL Error:",
            SDL_GetError());
    }
    return;
}

void sdl::ClearRender(objects::Renderer *renderer) {
    sdl::ClearRender(objects::toSdlRenderer(renderer));
}

void sdl::ClearRender(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
}

void sdl::RenderFrame(objects::Renderer *renderer) {
    return sdl::RenderFrame(
        objects::toSdlRenderer(renderer));
}

void sdl::RenderFrame(SDL_Renderer *renderer) {
    SDL_RenderPresent(renderer);
}
