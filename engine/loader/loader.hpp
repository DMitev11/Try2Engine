#pragma once
#include <texture_object.h>
#ifdef USE_SDL
#include "sdl_loader.h"
#endif
namespace loader {
    template <typename... Args>
    static objects::Texture *loadTexture(Args...);
#ifdef USE_SDL
    using LoadingTextureConfig = sdl::LoadingTextureConfig;
#endif
} // namespace loader

#ifdef USE_SDL
template <typename... Args>
inline static objects::Texture *
loader::loadTexture(Args... args) {
    return sdl::loadTexture(args...);
}
#endif
