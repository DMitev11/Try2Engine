#pragma once
#include "sdl_renderer_object.h"
#include "sdl_texture_object.h"
#include "sdl_window_object.h"
namespace objects
{
    inline SDL_Window *
    toSdlWindow(objects::Window *window)
    {
        objects::SDLWindow *const _window = static_cast<objects::SDLWindow *>(window);
        return (SDL_Window *)*_window;
    };
    inline SDL_Window *
    toSdlWindow(objects::Renderer *renderer)
    {
        objects::SDLRenderer *const _renderer = static_cast<objects::SDLRenderer *>(renderer);
        return (SDL_Window *)*_renderer;
    };
    inline SDL_Renderer *
    toSdlRenderer(objects::Renderer *renderer)
    {
        objects::SDLRenderer *const _renderer = static_cast<objects::SDLRenderer *>(renderer);
        return (SDL_Renderer *)*_renderer;
    };

    inline SDL_Texture *
    toSdlTexture(objects::Texture *texture)
    {
        objects::SDLTexture *const _texture = static_cast<objects::SDLTexture *>(texture);
        return (SDL_Texture *)*_texture;
    };
    inline SDL_Surface *
    toSdlSurface(objects::Texture *texture)
    {
        objects::SDLTexture *const _texture = static_cast<objects::SDLTexture *>(texture);
        return (SDL_Surface *)*_texture;
    };
} // namespace objects