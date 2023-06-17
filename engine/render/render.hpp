#pragma once
#include <renderer_object.h>
/**
 * @brief Rendering interactions. \n Initialize or shutdown
 * a rendering library/libraries. \n Create or terminate a
 * renderer based on ext. libraries
 *
 */
namespace render {

    /**
     * @brief Initialize rendering external
     * library/libraries, used to create a renderer
     *
     * @tparam Args Variations of flags used to during
     * initialization, based on the library used to create a
     * renderer
     * @return true: Successful initialization - does not
     * emit any logger messages. \n false: Unsuccessful -
     * log errors are emitted for more information
     */
    template <typename... Args> static bool init(Args...);

    /**
     * @brief Create a Renderer object, to hook on a
     * pre-initialized window. \n Display images, objects,
     * textures etc.
     *
     * @param args variadic, depends on the library used to
     * create a renderer
     * @return success: objects::Renderer* on success \n
     * fail: nullptr, will emit an error message in the
     * logger
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
     * @param args variadic, depends on the library used for
     * renderer creation. Should be RGBA values 0-255
     * (r,g,b,a)
     */
    template <typename... Args>
    static void SetDrawColor(Args...);

    /**
     * @brief Render an asset(texture, image, etc.) during
     * the next frame
     *
     * @param renderer which should render that asset
     * @tparam args variadic type and amount of parameters,
     * depending on the library used to implement the call
     */
    template <typename... Args>
    static void RenderAsset(objects::Renderer *renderer,
                            Args... args);

    /**
     * @brief Clear frame to a solid color. Preparation for
     * next frame
     *
     * @param renderer to clear
     */
    static void ClearRender(objects::Renderer *renderer);

    /**
     * @brief Render all buffered data between the previous
     * rendered frame and the one to-be-rendered
     *
     * @param renderer to render its next frame
     */
    static void RenderFrame(objects::Renderer *renderer);

    /**
     * @brief Get the size of a 2D texture.
     * @note Should be renamed to `Get2DTextureSize`
     *
     * @param texture to get the size of
     * @return objects::TextureSize width and height
     */
    static objects::TextureSize
    GetTextureSize(objects::Texture *texture);

    /**
     * @brief Destroy renderer and cleanup after
     *
     * @param renderer Renderer object ot be terminated
     */
    static void terminate(objects::Renderer *renderer);

    /**
     * @brief Shutdown rendering library/libraries
     * @warning Do not call until last frame of all
     * renderers, or the application itself - could lead to
     * unhandled exceptions and undefined behaviour
     *
     * @tparam Args Flags and settings to be cleaned-up
     * before closing
     */
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
inline static void
render::RenderAsset(objects::Renderer *renderer,
                    Args... args) {
    return sdl::RenderAsset(renderer, args...);
}

inline static objects::TextureSize
render::GetTextureSize(objects::Texture *texture) {
    return sdl::GetTextureSize(texture);
}

inline static void
render::ClearRender(objects::Renderer *renderer) {
    return sdl::ClearRender(renderer);
}

inline static void
render::RenderFrame(objects::Renderer *renderer) {
    return sdl::RenderFrame(renderer);
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