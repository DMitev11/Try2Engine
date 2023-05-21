#pragma once
#include <SDL3/SDL.h>
#include <vector>

#include "renderer_object.h"
namespace objects
{
    class SDLRenderer : public Renderer
    {
      public:
        SDLRenderer(SDL_Renderer *renderer, SDL_Window *window, const char *driverName, std::vector<uint32_t> initFlags) : Renderer()
        {
            this->renderer = renderer;
            this->window = window;
            this->driverName = driverName;
            this->initFlags = initFlags;
        }
        ~SDLRenderer() = default;

        operator SDL_Renderer *()
        {
            return this->renderer;
        }

      private:
        SDL_Renderer *renderer;
        SDL_Window *window;
        const char *driverName;
        std::vector<uint32_t> initFlags;
    };
} // namespace objects