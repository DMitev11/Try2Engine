#pragma once
#include "texture_object.h"
#include <SDL3/SDL.h>
namespace objects {
    class SDLTexture : public Texture {
      public:
        SDLTexture(const char *path, int width, int height,
                   SDL_Texture *texture)
            : Texture(path, width, height) {
            this->texture = texture;
        }
        ~SDLTexture() = default;
        operator SDL_Texture *() { return this->texture; }

      protected:
        SDL_Texture *texture;
    };
} // namespace objects