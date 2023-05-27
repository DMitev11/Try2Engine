#pragma once
#include "texture_object.h"
namespace loader
{
    template <typename... Args>
    static objects::Texture *
    LoadTexture(Args...);
} // namespace loader
#ifdef SDL_USED
#include "sdl_loader.h"

template <typename... Args>
inline static objects::Texture *
loader::LoadTexture(Args... args)
{
    return sdl::LoadTexture(args...);
}
#endif
