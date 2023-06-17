#pragma once

#include <SDL3/SDL.h>
#include <renderer_object.h>
#include <texture_object.h>
#include <vector>
#include <window_object.h>

#ifdef USE_SDL_IMAGE
#include <SDL_image.h>
#endif
namespace render {
    namespace sdl {
        /**
         * @brief Default initialization flags, used to
         * start module/s of SDL used during rendering
         *
         * @note Each flag represents a different part of
         * SDL which can be utilized. `SDL_INIT_VIDEO` is
         * the default flag for renderer creation
         * @see SDL_init.h#SDL_InitFlags
         *
         */
        const std::vector<uint32_t> kDefaultInitFlags = {
            SDL_INIT_VIDEO};

#ifdef USE_SDL_IMAGE
        extern bool
        init(std::vector<uint32_t> initFlags =
                 kDefaultInitFlags,
             std::vector<uint32_t> imageInitFlags = {
                 IMG_INIT_JPG, IMG_INIT_PNG});
#else
        /**
         * @brief Initialize SDL rendering libary.
         *
         * @param initFlags Used to initialize modules of
         * SDL used for rendering
         * @see kDefaultInitFlags
         * @return true Successful - no logs should
         * emit
         * @return false Unsuccessful - emits logs for
         * further information
         */
        extern bool init(std::vector<uint32_t> initFlags =
                             kDefaultInitFlags);
#endif
        /**
         * @brief Create a Renderer object to render on
         *
         * @param window To bind the renderer on
         * @param driverName Name of the video driver which
         * should be used for rendering. Defaults to first
         * find video driver if `0` used as argument
         * @param initFlags Used during renderer creation
         * @see SDL_render.h#SDL_RendererFlags
         * @return objects::Renderer*
         */
        extern objects::Renderer *
        CreateRenderer(objects::Window *window,
                       const char *driverName = 0,
                       std::vector<uint32_t> initFlags = {
                           SDL_RENDERER_ACCELERATED});

        /**
         * @see CreateRenderer
         */
        extern objects::Renderer *
        CreateRenderer(SDL_Window *window,
                       const char *driverName = 0,
                       std::vector<uint32_t> initFlags = {
                           SDL_RENDERER_ACCELERATED});

        /**
         * @brief Set the drawing color, if renderer is used
         * to draw clear colors.
         * @see ClearRenderer
         *
         * @param renderer to set the drawing color for
         * @param r 0-255
         * @param g 0-255
         * @param b 0-255
         * @param a 0-255
         */
        extern void
        SetDrawColor(objects::Renderer *renderer, uint8_t r,
                     uint8_t g, uint8_t b, uint8_t a);

        /**
         * @see SetDrawColor
         */
        extern void SetDrawColor(SDL_Renderer *renderer,
                                 uint8_t r, uint8_t g,
                                 uint8_t b, uint8_t a);

        /**
         * @brief Draw a 2D asset(texture, img etc.) on the
         * screen during next frame
         * @note Should be renamed to `Render2DAsset`
         * @param renderer To render the asset on
         * @param texture To render
         * @param x on the window
         * @param y on the window
         */
        extern void RenderAsset(objects::Renderer *renderer,
                                objects::Texture *texture,
                                float x, float y);
        /**
         * @see RenderAsset
         */
        extern void RenderAsset(SDL_Renderer *renderer,
                                SDL_Texture *texture,
                                float w, float h, float x,
                                float y);
        /**
         * @brief Get the width and height of a 2D asset
         * @note Should be renamed to `Get2DTextureSize`
         *
         * @param texture size of which should be received
         * @return objects::TextureSize width and height
         */
        extern objects::TextureSize
        GetTextureSize(objects::Texture *texture);
        /**
         * @see GetTextureSize
         */
        extern objects::TextureSize
        GetTextureSize(SDL_Texture *texture);

        /**
         * @see render.hpp#ClearRender
         */
        extern void
        ClearRender(objects::Renderer *renderer);

        /**
         * @see render.hpp#ClearRender
         */
        extern void ClearRender(SDL_Renderer *renderer);

        /**
         * @see render.hpp#RenderFrame
         */
        extern void
        RenderFrame(objects::Renderer *renderer);

        /**
         * @see render.hpp#RenderFrame
         */
        extern void RenderFrame(SDL_Renderer *renderer);

        /**
         * @see render.hpp#terminate
         */
        extern void terminate(objects::Renderer *renderer);

        /**
         * @see render.hpp#terminate
         */
        extern void terminate(SDL_Renderer *renderer);

        /**
         * @brief Shutdown all rendering related modules of
         * SDL
         * @warning Do not call until last frame of all
         * renderers, or the application itself - could lead
         * to unhandled exceptions and undefined behaviour
         *
         * @param initFlags for each module.
         * @see kDefaultInitFlags
         */
        extern void
        shutdown(std::vector<uint32_t> initFlags =
                     kDefaultInitFlags);
    }; // namespace sdl
} // namespace render