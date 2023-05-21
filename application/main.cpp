#include <iostream>
#include <stdexcept>

#include "engine/initialization/initialization.hpp"
#include "engine/objects/sdl_window_object.h"
#include "engine/render/render.hpp"
#include "engine/window/window.hpp"
int
main(int argc, char const *argv[])
{
    if (!initialization::Init())
    {
        std::string err = "Cannot initialize";
        std::cout << err;
        throw std::runtime_error(err);
    }
    objects::SDLWindow *window = window::CreateWindow(1000, 1000, "Try2Engine Application");
    const objects::Renderer *renderer = render::CreateRenderer(window); /* code */
};