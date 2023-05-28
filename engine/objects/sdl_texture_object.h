#pragma once
#include "texture_object.h"
#include <SDL3/SDL.h>
namespace objects
{
    class SDLTexture : public Texture
    {
      public:
        SDLTexture(const char *path, SDL_Surface *surface, SDL_Texture *texture) : Texture(path, surface->w, surface->h)
        {
            this->surface = surface;
            this->texture = texture;
        }
        ~SDLTexture() = default;
        operator SDL_Texture *()
        {
            return this->texture;
        }
        operator SDL_Surface *()
        {
            return this->surface;
        }

      protected:
        SDL_Surface *surface;
        SDL_Texture *texture;
    };
} // namespace objects