#include "sdl_renderer.h"
#include <helpers_object.hpp>
#include <logger/logger.h>
#include <sdl_renderer_object.h>
#include <sdl_texture_object.h>
#include <sdl_window_object.h>
#include <stdexcept>
#include <vector>
using namespace render;

bool initialize(std::vector<uint32_t> initFlags) {
    uint32_t flags = 0;
    for each (uint32_t flag in initFlags) {
        // Initialize the flag if necessary
        auto res = SDL_WasInit(flag);
        if (flag != SDL_WasInit(flag)) {
            flags = flags | flag;
        }
    }
    // Initialize SDL
    if (SDL_Init(flags) < 0) {
        LOG_ENGINE_ERROR(
            "SDL could not initialize! SDL Error: ",
            SDL_GetError());
        return false;
    }

    return true;
}

#ifndef USE_SDL_IMAGE
bool sdl::init(std::vector<uint32_t> initFlags) {
    return initialize(initFlags);
}
#else
bool initializeImg(std::vector<uint32_t> imageInitFlags) {
    int imgFlags = 0;
    for each (int flag in imageInitFlags) {
        imgFlags = flag | imgFlags;
    }
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        LOG_ENGINE_ERROR(
            "SDL_image could not initialize! SDL_image "
            "Error: ",
            IMG_GetError());
        return false;
    }
    return true;
}
bool sdl::init(std::vector<uint32_t> initFlags,
               std::vector<uint32_t> imageInitFlags) {
    return initialize(initFlags) &&
           initializeImg(imageInitFlags);
}
#endif

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

void sdl::terminate(objects::Renderer *renderer) {
    return sdl::terminate(
        (SDL_Renderer *)static_cast<objects::SDLRenderer *>(
            renderer));
}
void sdl::terminate(SDL_Renderer *renderer) {
    SDL_DestroyRenderer(renderer);
    auto err = SDL_GetError();
    if (err != "") {
        LOG_ENGINE_ERROR("Renderer: ", err);
    }
    return;
}
void sdl::shutdown(std::vector<uint32_t> initFlags) {
    uint32_t flags = 0;
    for each (uint32_t flag in initFlags) {
        // Initialize the flag if necessary
        if (flag == SDL_WasInit(flag)) {
            flags = flags | flag;
        }
    }
    SDL_QuitSubSystem(flags);
}
