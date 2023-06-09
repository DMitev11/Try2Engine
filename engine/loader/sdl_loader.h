#pragma once
#include <renderer_object.h>
#include <texture_object.h>
#include <SDL3/SDL.h>
namespace loader
{
    namespace sdl
    {
        struct LoadingTextureConfig
        {
            struct ColorKey
            {
                uint8_t r;
                uint8_t g;
                uint8_t b;
            };
            ColorKey colorKey;
        };
        extern objects::Texture*
            loadTexture(objects::Renderer* renderer, const char* path, LoadingTextureConfig config = LoadingTextureConfig());
    }; // namespace sdl
} // namespace loader