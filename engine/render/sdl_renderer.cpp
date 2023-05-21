#include "sdl_renderer.h"
#include "sdl_renderer_object.h"
#include "sdl_window_object.h"
#include <stdexcept>
#include <vector>
using namespace render;

objects::Renderer *
sdl::CreateRenderer(objects::Window *window, const char *driverName, std::vector<uint32_t> initFlags)
{
    objects::SDLWindow *const _window = static_cast<objects::SDLWindow *>(window);
    return sdl::CreateRenderer((SDL_Window *)*_window, driverName, initFlags);
}

objects::Renderer *
sdl::CreateRenderer(SDL_Window *window, const char *driverName, std::vector<uint32_t> initFlags)
{
    uint32_t flags = 0;
    for each (uint32_t flag in initFlags)
    {
        flags = flags | flag;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL, flags);
    if (renderer == NULL)
    {
        std::string err = ("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        throw std::runtime_error(err);
    }
    return new objects::SDLRenderer(renderer, window, driverName, initFlags);
}

void
sdl::SetDrawColor(objects::Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    const objects::Renderer *_window = static_cast<objects::SDLRenderer *>(renderer);
    sdl::SetDrawColor((SDL_Renderer *)&renderer, r, g, b, a);
}

void
sdl::SetDrawColor(SDL_Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}