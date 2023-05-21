#pragma once
#include <vector>

#include "window_object.h"
namespace window
{
    namespace sdl
    {
        extern objects::Window
        createWindow(int height, int width, const char *title, std::vector<uint32_t> flags);
    }
}; // namespace window
