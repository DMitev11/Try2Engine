#pragma once
#include "renderer_object.h"
namespace render
{
    template <typename... Args>
    static objects::Renderer
    createRenderer(Args...);

    template <typename... Args>
    static void
    setDrawColor(Args...);
} // namespace render

#ifdef SDL_USED
#include "sdl_renderer.h"
template <typename... Args>
inline static objects::Renderer
render::createRenderer(Args... args)
{
    return sdl::createRenderer(args...)
}
template <typename... Args>
inline static void
render::setDrawColor(Args... args)
{
    return sdl::setDrawColor(args...)
}

#endif