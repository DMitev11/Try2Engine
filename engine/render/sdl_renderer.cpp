#include "sdl_renderer.h"
#include "sdl_renderer_object.h"
#include "sdl_texture_object.h"
#include "sdl_window_object.h"
#include <stdexcept>
#include <vector>
using namespace render;

SDL_Window *
objectToSdl(objects::Window *window)
{
    objects::SDLWindow *const _window = static_cast<objects::SDLWindow *>(window);
    return (SDL_Window *)*_window;
}
SDL_Renderer *
objectToSdl(objects::Renderer *renderer)
{
    objects::SDLRenderer *const _renderer = static_cast<objects::SDLRenderer *>(renderer);
    return (SDL_Renderer *)*_renderer;
}
SDL_Texture *
objectToSdl(objects::Texture *texture)
{
    objects::SDLTexture *const _texture = static_cast<objects::SDLTexture *>(texture);
    return (SDL_Texture *)*_texture;
}
objects::Renderer *
sdl::CreateRenderer(objects::Window *window, const char *driverName, std::vector<uint32_t> initFlags)
{
    return sdl::CreateRenderer(objectToSdl(window), driverName, initFlags);
}

objects::Renderer *
sdl::CreateRenderer(SDL_Window *window, const char *driverName, std::vector<uint32_t> initFlags)
{
    uint32_t flags = 0;
    for each (uint32_t flag in initFlags)
    {
        flags = flags | flag;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, SDL_GetHint(SDL_HINT_RENDER_DRIVER), flags);
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
    sdl::SetDrawColor(objectToSdl(renderer), r, g, b, a);
}

void
sdl::SetDrawColor(SDL_Renderer *renderer, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void
sdl::RenderAsset(objects::Renderer *renderer, objects::Texture *texture, float x, float y)
{
    return sdl::RenderAsset(objectToSdl(renderer), objectToSdl(texture), (float)texture->width, (float)texture->height, x, y);
}

void
sdl::RenderAsset(SDL_Renderer *renderer, SDL_Texture *texture, float w, float h, float x, float y)
{
    SDL_FRect quad = {x, y, w, h};
    int res = SDL_RenderTexture(renderer, texture, 0, &quad);
    const char *err = SDL_GetError();
    return;
}

void
sdl::ClearRender(objects::Renderer *renderer)
{
    sdl::ClearRender(objectToSdl(renderer));
}

void
sdl::ClearRender(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer);
}

void
sdl::RenderFrame(objects::Renderer *renderer)
{
    return sdl::RenderFrame(objectToSdl(renderer));
}

void
sdl::RenderFrame(SDL_Renderer *renderer)
{
    SDL_RenderPresent(renderer);
}
