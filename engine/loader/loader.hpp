#pragma once
#include <texture_object.h>
#ifdef USE_SDL
#include "sdl_loader.h"
#endif
namespace loader {

    /**
     * @brief Initialize file loading external
     * library/libraries, used to create textures etc.
     *
     * @tparam Args Variations of flags used during
     * initialization, based on the library/libraries
     *
     * @return true: Successful initialization - does not
     * emit any logger messages. \n false: Unsuccessful -
     * log errors are emitted for more information
     */
    template <typename... Args> static bool init(Args...);

    template <typename... Args>
    static objects::Texture *loadTexture(Args...);
#ifdef USE_SDL
    using LoadingTextureConfig = sdl::LoadingTextureConfig;
#endif
} // namespace loader

#ifdef USE_SDL
template <typename... Args>
inline static bool loader::init(Args... args) {
    return sdl::init(args...);
}
template <typename... Args>
inline static objects::Texture *
loader::loadTexture(Args... args) {
    return sdl::loadTexture(args...);
}
#endif
