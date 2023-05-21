#pragma once
#include "renderer_object.h"
#include <vector>
namespace render
{
    template <typename... Args>
    static objects::Renderer *
    CreateRenderer(Args...);

    template <typename... Args>
    static void
    SetDrawColor(Args...);

} // namespace render
#ifdef SDL_USED
#include "sdl_renderer.h"

template <typename... Args>
inline static objects::Renderer *
render::CreateRenderer(Args... args)
{
    return sdl::CreateRenderer(args...);
}
template <typename... Args>
inline static void
render::SetDrawColor(Args... args)
{
    return sdl::SetDrawColor(args...);
}

#endif