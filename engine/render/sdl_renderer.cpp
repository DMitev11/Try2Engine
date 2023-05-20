#include <vector>
#include <stdexcept>
#include "sdl_renderer.h"
#include "sdl_renderer_object.h"
using namespace render;
objects::Renderer sdl::createRenderer(SDL_Window* window, const char* driverName, std::vector<uint32_t> initFlags) {
    uint32_t flags = 0;
    for each (uint32_t flag in initFlags) {
        flags = flags | flag;
    }
    SDL_Renderer* renderer = SDL_CreateRenderer(window, driverName, flags);
    if (renderer == NULL)
    {
        std::string err = ("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        throw std::runtime_error(err);
    }
    return objects::SDLRenderer(renderer, window, driverName, initFlags);
}

void sdl::setDrawColor(objects::SDLRenderer renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

}