#include "sdl_loader.h"
#include <SDL3/SDL.h>
#include <helpers_object.hpp>
#include <logger/logger.h>
#include <sdl_renderer_object.h>
#include <sdl_texture_object.h>
#include <stdio.h>
#include <string>

#ifdef USE_SDL_IMAGE
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
bool sdl::init(std::vector<uint32_t> imageInitFlags) {
    return initializeImg(imageInitFlags);
}
#else
bool loader::sdl::init() { return true; }
#endif

#ifdef USE_STB
#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif
#include <libraries/stb/stb_image.h>
#ifndef STBI_MALLOC
#define STBI_MALLOC
#endif
#ifndef STBI_REALLOC
#define STBI_REALLOC
#endif
#ifndef STBI_FREE
#define STBI_FREE
#endif

objects::Texture *
loadTexture(SDL_Window *window, SDL_Renderer *renderer,
            const char *path,
            loader::sdl::LoadingTextureConfig config) {
    int width, height, channels;
    unsigned char *image_data = stbi_load(
        path, &width, &height, &channels, STBI_rgb_alpha);

    SDL_Surface *surface = SDL_CreateSurfaceFrom(
        image_data, width, height, 4 * width,
        SDL_PIXELFORMAT_RGBA32);

    Uint32 colorKey =
        SDL_MapRGB(surface->format, 255, 0, 255);
    SDL_SetSurfaceColorKey(surface, SDL_TRUE, colorKey);

    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(renderer, surface);

    return new objects::SDLTexture(path, surface->w,
                                   surface->h, texture);
}
#endif

#ifdef USE_SDL_IMAGE
#include <SDL_image.h>

objects::Texture *

loadTexture(SDL_Window *window, SDL_Renderer *renderer,
            const char *path,
            loader::sdl::LoadingTextureConfig config) {
    SDL_Surface *surface = IMG_Load(path);
    if (surface) {
        SDL_SetSurfaceColorKey(
            surface, SDL_TRUE,
            SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        surface = SDL_ConvertSurfaceFormat(
            surface, SDL_GetWindowPixelFormat(window));
        if (!surface) {
            LOG_ENGINE_ERROR(
                "Unable to convert loaded surface to "
                "display format! SDL Error: ",
                SDL_GetError());
            goto invalid;
        }
        SDL_Texture *texture =
            SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            LOG_ENGINE_ERROR(
                "Unable to create texture from loaded "
                "pixels! SDL Error:",
                SDL_GetError());
            goto invalid;
        }

        SDL_DestroySurface(surface);
        return new objects::SDLTexture(path, surface->w,
                                       surface->h, texture);
    } else {
        LOG_ENGINE_ERROR("Unable to load image: ",
                         IMG_GetError());
        LOG_ENGINE_ERROR("SDL Error: ", SDL_GetError());

        goto invalid;
    }

invalid:
    return nullptr;
}
#endif

objects::Texture *
loader::sdl::loadTexture(objects::Renderer *renderer,
                         const char *path,
                         sdl::LoadingTextureConfig config) {
    objects::SDLRenderer *_renderer =
        static_cast<objects::SDLRenderer *>(renderer);

    return loadTexture(objects::toSdlWindow(_renderer),
                       objects::toSdlRenderer(_renderer),
                       path, config);
}
