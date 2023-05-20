#pragma once
#include "window_object.h"
#include <SDL3/SDL_video.h>
namespace objects {
    class SDLWindow final: public Window {
    public:
        SDLWindow(SDL_Window* window, int height, int width, std::string title)
            : Window(height, width, title) {
            this->window = window;
        }
    private:
        SDL_Window* window;
    };
}

