#pragma once
#include "renderer_object.h"
namespace render
{
    template <typename... Args>
    static objects::Renderer *
    CreateRenderer(Args...);

    template <typename... Args>
    static void
    SetDrawColor(Args...);

    template <typename... Args>
    static void
    RenderAsset(Args...);

    template <typename... Args>
    static void
    ClearRender(Args...);

    template <typename... Args>
    static void
    RenderFrame(Args...);

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

template <typename... Args>
inline static void
render::RenderAsset(Args... args)
{
    return sdl::RenderAsset(args...);
}

template <typename... Args>
inline static void
render::ClearRender(Args... args)
{
    return sdl::ClearRender(args...);
}

template <typename... Args>
inline static void
render::RenderFrame(Args... args)
{
    return sdl::RenderFrame(args...);
}

#endif