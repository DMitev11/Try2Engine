#pragma once
#include <SDL3/SDL_video.h>

#include "window_object.h"
namespace objects
{
    class SDLWindow final : public Window
    {
      public:
        SDLWindow(SDL_Window *window, int height, int width, std::string title) : Window(height, width, title)
        {
            this->window = window;
        }

      private:
        SDL_Window *window;
    };
} // namespace objects
