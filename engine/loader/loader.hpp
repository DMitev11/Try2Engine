#pragma once
#include "texture_object.h"
#ifdef SDL_USED
#include "sdl_loader.h"
#endif
namespace loader
{
    template <typename... Args>
    static objects::Texture *
    LoadTexture(Args...);
#ifdef SDL_USED
    using LoadingTextureConfig = sdl::LoadingTextureConfig;
#endif
} // namespace loader

#ifdef SDL_USED
template <typename... Args>
inline static objects::Texture *
loader::LoadTexture(Args... args)
{
    return sdl::LoadTexture(args...);
}
#endif
