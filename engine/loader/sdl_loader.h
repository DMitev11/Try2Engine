#pragma once
#include <SDL3/SDL.h>
#include <renderer_object.h>
#include <texture_object.h>

#ifdef USE_SDL_IMAGE
#include <SDL_image.h>
#endif
namespace loader {
    namespace sdl {

#ifdef USE_SDL_IMAGE
        extern bool
        init(std::vector<uint32_t> imageInitFlags = {
                 IMG_INIT_JPG, IMG_INIT_PNG});
#else
        extern bool init();
#endif

        struct LoadingTextureConfig {
            struct ColorKey {
                uint8_t r;
                uint8_t g;
                uint8_t b;
            };
            ColorKey colorKey;
        };
        extern objects::Texture *
        loadTexture(objects::Renderer *renderer,
                    const char *path,
                    LoadingTextureConfig config =
                        LoadingTextureConfig());
    }; // namespace sdl
} // namespace loader