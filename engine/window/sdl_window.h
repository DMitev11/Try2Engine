#pragma once
#include "window_object.h"
#include <vector>
namespace window
{
    namespace sdl {
        static objects::Window createWindow(int height, int width, const char* title, std::vector<uint32_t> flags);
    }
};
