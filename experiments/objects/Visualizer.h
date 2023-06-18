#pragma once
#include "loader/loader.hpp"
#include "render/render.hpp"
#include "window/window.hpp"
namespace application
{
    template <typename T> struct ReturnValue
    {
        bool success;
        T data;
    };

    class Visualizer
    {
      public:
        static Visualizer *
        get();

        ReturnValue<objects::Window *>
        CreateWindow(int width, int height, const char *title);
        ReturnValue<objects::Renderer *>
        createRenderer();
        bool
        setDrawColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a);
        ReturnValue<objects::Texture *>
        LoadTexture(const char *path);
#ifdef USE_SDL
        ReturnValue<objects::Texture *>
        LoadTexture(const char *path, loader::sdl::LoadingTextureConfig config);
#endif
        bool
        RenderTexture(objects::Texture *texture, float x, float y);
        void
        ClearRenderer();
        void
        CallFrame();

      private:
        Visualizer() = default;
        ~Visualizer() = default;

      protected:
        bool
        Init();

        //@todo for later
        // template<typename T>
        // ReturnValue<T> Execute(<LAMBDA>)
        bool initialized;

        objects::Renderer *renderer;
        objects::Window *window;
    };
} // namespace application