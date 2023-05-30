#include "Visualizer.h"
#include "initialization/initialization.hpp"
#include "window/window.hpp"
#include <stdio.h>
using namespace application;

Visualizer *
Visualizer::get()
{
    static Visualizer vis;
    return &vis;
}
bool
Visualizer::Init()
{
    if (!initialization::Init())
    {
        throw std::runtime_error("Cannot initialize");
    }
    this->initialized = true;
    return this->initialized;
}

ReturnValue<objects::Window *>
Visualizer::CreateWindow(int width, int height, const char *title)
{
    if (!this->initialized)
    {
        printf("Not initialized");
        this->Init();
        // goto invalid;
    }
    if (this->window)
    {
        printf("Created already");
        goto invalid;
    }

    this->window = window::CreateWindow(width, height, title);
    return ReturnValue<objects::Window *>{true, window};

invalid:
    return ReturnValue<objects::Window *>{false, nullptr};
}

ReturnValue<objects::Renderer *>
Visualizer::CreateRenderer()
{
    if (!this->initialized)
    {
        printf("Not initialized");
        this->Init();
        // goto invalid;
    }
    else if (!this->window)
    {
        printf("Create window first");
        goto invalid;
    }

    if (this->renderer)
    {
        printf("Created already");
        goto invalid;
    }

    this->renderer = render::CreateRenderer(window);
    return ReturnValue<objects::Renderer *>{true, this->renderer};

invalid:
    return ReturnValue<objects::Renderer *>{false, nullptr};
}

bool
Visualizer::SetDrawColor(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    if (!this->initialized)
    {
        printf("Not initialized");
        goto invalid;
    }
    if (!this->window)
    {
        printf("Create window first");
        goto invalid;
    }
    if (!this->renderer)
    {
        printf("Create renderer first");
        goto invalid;
    }

    try
    {
        render::SetDrawColor(this->renderer, r, g, b, a);
        return true;
    }
    catch (const char *e)
    {
        printf(e);
        goto invalid;
    }
invalid:
    return false;
}

ReturnValue<objects::Texture *>
Visualizer::LoadTexture(const char *path)
{
    if (!this->initialized)
    {
        printf("Not initialized");
        goto invalid;
    }
    if (!this->window)
    {
        printf("Create window first");
        goto invalid;
    }
    if (!this->renderer)
    {
        printf("Create renderer first");
        goto invalid;
    }

    try
    {
        return ReturnValue<objects::Texture *>{true, loader::LoadTexture(this->renderer, path)};
    }
    catch (const char *e)
    {
        printf(e);
        goto invalid;
    }
invalid:
    return ReturnValue<objects::Texture *>{false, nullptr};
}

#ifdef SDL_USED
ReturnValue<objects::Texture *>
Visualizer::LoadTexture(const char *path, loader::LoadingTextureConfig config)
{

    if (!this->initialized)
    {
        printf("Not initialized");
        goto invalid;
    }
    if (!this->window)
    {
        printf("Create window first");
        goto invalid;
    }
    if (!this->renderer)
    {
        printf("Create renderer first");
        goto invalid;
    }

    try
    {
        return ReturnValue<objects::Texture *>{true, loader::LoadTexture(this->renderer, path, config)};
    }
    catch (const char *e)
    {
        printf(e);
        goto invalid;
    }
invalid:
    return ReturnValue<objects::Texture *>{false, nullptr};
}
#endif
bool
Visualizer::RenderTexture(objects::Texture *texture, float x, float y)
{

    if (!this->initialized)
    {
        printf("Not initialized");
        goto invalid;
    }
    if (!this->window)
    {
        printf("Create window first");
        goto invalid;
    }
    if (!this->renderer)
    {
        printf("Create renderer first");
        goto invalid;
    }

    try
    {
        render::RenderAsset(this->renderer, texture, x, y);
        return true;
    }
    catch (const char *e)
    {
        printf(e);
        goto invalid;
    }
invalid:
    return false;
}

void
Visualizer::ClearRenderer()
{
    if (!this->initialized)
    {
        printf("Not initialized");
        return;
    }
    if (!this->window)
    {
        printf("Create window first");
        return;
    }
    if (!this->renderer)
    {
        printf("Create renderer first");
        return;
    }
    try
    {
        render::ClearRender(this->renderer);
        return;
    }
    catch (const char *e)
    {
        printf(e);
        return;
    }
}

void
Visualizer::CallFrame()
{
    if (!this->initialized)
    {
        printf("Not initialized");
        return;
    }
    if (!this->window)
    {
        printf("Create window first");
        return;
    }
    if (!this->renderer)
    {
        printf("Create renderer first");
        return;
    }
    try
    {
        render::RenderFrame(this->renderer);
        return;
    }
    catch (const char *e)
    {
        printf(e);
        return;
    }
}