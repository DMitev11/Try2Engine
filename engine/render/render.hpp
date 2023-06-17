#pragma once
#include <renderer_object.h>
namespace render {

    template <typename... Args> static bool init(Args...);
    /**
     * @brief Create a Renderer object, to hook on a
     * pre-initialized window Display images, objects,
     * textures etc.
     *
     * @param args variadic, depends on the package used for
     * renderer creation
     * @return objects::Renderer* on success, nullptr
     * on fail (should emit an error message in the logger)
     *
     * @see objects::Renderer
     */
    template <typename... Args>
    static objects::Renderer *CreateRenderer(Args...);

    /**
     * @brief Set a default draw color.
     * Could be interpreted as the background color of a
     * clear frame
     *
     * @param args variadic, depends on the package used for
     * renderer creation. Should be RGBA values 0-255
     * (r,g,b,a)
     */
    template <typename... Args>
    static void SetDrawColor(Args...);

    template <typename... Args>
    static void RenderAsset(Args...);

    /**
     * @brief Clear frame to a solid color
     */
    template <typename... Args>
    static void ClearRender(Args...);

    /**
     * @brief Render all buffered data between the previous
     * rendered frame and the one to-be-rendered
     */
    template <typename... Args>
    static void RenderFrame(Args...);

    static objects::TextureSize
    GetTextureSize(objects::Texture *texture);

    template <typename... Args>
    static void terminate(Args...);

    template <typename... Args>
    static void shutdown(Args...);

} // namespace render
#ifdef USE_SDL
#include "sdl_renderer.h"

template <typename... Args>
inline static bool render::init(Args... args) {
    return sdl::init(args...);
}
template <typename... Args>
inline static objects::Renderer *
render::CreateRenderer(Args... args) {
    return sdl::CreateRenderer(args...);
}
template <typename... Args>
inline static void render::SetDrawColor(Args... args) {
    return sdl::SetDrawColor(args...);
}

template <typename... Args>
inline static void render::RenderAsset(Args... args) {
    return sdl::RenderAsset(args...);
}

inline static objects::TextureSize
render::GetTextureSize(objects::Texture *texture) {
    return sdl::GetTextureSize(texture);
}

template <typename... Args>
inline static void render::ClearRender(Args... args) {
    return sdl::ClearRender(args...);
}

template <typename... Args>
inline static void render::RenderFrame(Args... args) {
    return sdl::RenderFrame(args...);
}

template <typename... Args>
inline static void render::terminate(Args... args) {
    return sdl::terminate(args...);
}
template <typename... Args>
inline static void render::shutdown(Args... args) {
    return sdl::shutdown(args...);
}
#endif