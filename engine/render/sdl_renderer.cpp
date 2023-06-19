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

    // As of SDL's implementation, each flag should be OR'ed
    // with the rest into an unsigned 32 bit integer
    uint32_t flags = 0;
    for (int i = 0; i < initFlags.size(); i++) {
        if (initFlags[i] != SDL_WasInit(initFlags[i])) {
            flags |= initFlags[i];
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
    for (int i = 0; i < imageInitFlags.size(); i++) {
        imgFlags |= imageInitFlags[i];
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
sdl::createRenderer(objects::Window *window,
                    const char *driverName,
                    std::vector<uint32_t> initFlags) {
    return sdl::createRenderer(objects::toSdlWindow(window),
                               driverName, initFlags);
}

objects::Renderer *
sdl::createRenderer(SDL_Window *window,
                    const char *driverName,
                    std::vector<uint32_t> initFlags) {

    // As of SDL's implementation, each flag should be OR'ed
    // with the rest into an unsigned 32 bit integer
    uint32_t flags = 0;
    for (int i = 0; i < initFlags.size(); i++) {
        flags |= initFlags[i];
    }

    /**
     * @see SDL_hints.h for hints
     */
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

void sdl::setDrawColor(objects::Renderer *renderer,
                       uint8_t r, uint8_t g, uint8_t b,
                       uint8_t a) {
    sdl::setDrawColor(objects::toSdlRenderer(renderer), r,
                      g, b, a);
}

void sdl::setDrawColor(SDL_Renderer *renderer, uint8_t r,
                       uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void sdl::renderAsset(objects::Renderer *renderer,
                      objects::Texture *texture, float x,
                      float y) {
    return sdl::renderAsset(
        objects::toSdlRenderer(renderer),
        objects::toSdlTexture(texture),
        (float)texture->kWidth, (float)texture->kHeight, x,
        y);
}

void sdl::renderAsset(SDL_Renderer *renderer,
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

objects::TextureSize
sdl::getTextureSize(objects::Texture *texture) {
    return sdl::getTextureSize(
        objects::toSdlTexture(texture));
}

objects::TextureSize
sdl::getTextureSize(SDL_Texture *texture) {

    int width = 0;
    int height = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &width,
                     &height);
    return objects::TextureSize(width, height);
}

void sdl::clearRenderer(objects::Renderer *renderer) {
    sdl::clearRenderer(objects::toSdlRenderer(renderer));
}

void sdl::clearRenderer(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
}

void sdl::renderFrame(objects::Renderer *renderer) {
    return sdl::renderFrame(
        objects::toSdlRenderer(renderer));
}

void sdl::renderFrame(SDL_Renderer *renderer) {
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

    // As of SDL's implementation, each flag should be OR'ed
    // with the rest into an unsigned 32 bit integer
    uint32_t flags = 0;
    for (int i = 0; i < initFlags.size(); i++) {
        // Initialize the flag if necessary
        if (initFlags[i] == SDL_WasInit(initFlags[i])) {
            flags |= initFlags[i];
        }
    }
    SDL_QuitSubSystem(flags);
}
