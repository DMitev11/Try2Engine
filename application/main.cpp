#include <iostream>
#include <stdexcept>

#include "./objects/Visualizer.h"
#include "engine/initialization/initialization.hpp"
#include "engine/objects/sdl_texture_object.h"
#include "engine/objects/sdl_window_object.h"
int
main(int argc, char const *argv[])
{
    application::Visualizer *vis = application::Visualizer::get();
    vis->CreateWindow(1000, 1000, "hello");
    vis->CreateRenderer();
    vis->SetDrawColor(255, 255, 255, 50);
    auto res = vis->LoadTexture("assets/linus.jpg", loader::LoadingTextureConfig());
    if (!res.success)
    {
        printf("failed");
        return 0;
    }
    objects::Texture *texture = res.data;
    objects::SDLTexture *texture2 = static_cast<objects::SDLTexture *>(res.data);
    float x = 0.f;
    float y = 0.f;
    while (true)
    {
        vis->SetDrawColor(0xFF, 0xFF, 0xFF, 0);
        vis->ClearRenderer();
        vis->RenderTexture(texture, x, y);
        vis->CallFrame();
    }
};