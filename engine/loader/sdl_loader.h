#pragma once

#include "renderer_object.h"
#include "texture_object.h"
#include <SDL3/SDL.h>
namespace loader
{
    namespace sdl
    {
        extern objects::Texture *
        LoadTexture(objects::Renderer *renderer, const char *path);
        extern objects::Texture *
        LoadTexture(SDL_Window *window, SDL_Renderer *renderer, const char *path);
    }; // namespace sdl
} // namespace loader