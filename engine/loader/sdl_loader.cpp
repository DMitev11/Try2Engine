#include "sdl_loader.h"
#include "sdl_renderer_object.h"
#include "sdl_texture_object.h"
#include <SDL3/SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "helpers_object.hpp"
using namespace loader;
objects::Texture *
loadTexture(SDL_Window *window, SDL_Renderer *renderer, const char *path, sdl::LoadingTextureConfig config)
{
    SDL_Surface *surface = IMG_Load(path);
    if (surface)
    {
        SDL_SetSurfaceColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
        surface = SDL_ConvertSurfaceFormat(surface, SDL_GetWindowPixelFormat(window));
        if (!surface)
        {
            printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
            goto invalid;
        }
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture)
        {
            printf("Unable to create texture from loaded pixels! SDL Error: %s\n", SDL_GetError());
            goto invalid;
        }

        SDL_DestroySurface(surface);
        return new objects::SDLTexture(path, surface, texture);
    }
    else
    {
        printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
        goto invalid;
    }

invalid:
    return nullptr;
}

objects::Texture *
sdl::LoadTexture(objects::Renderer *renderer, const char *path, sdl::LoadingTextureConfig config)
{
    objects::SDLRenderer *_renderer = static_cast<objects::SDLRenderer *>(renderer);

    return loadTexture(objects::toSdlWindow(_renderer), objects::toSdlRenderer(_renderer), path, config);
}
