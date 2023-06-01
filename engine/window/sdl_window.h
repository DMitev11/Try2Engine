#pragma once
#include <vector>

#include "sdl_window_object.h"
#include "window_object.h"
namespace window {
    namespace sdl {
        const std::vector<uint32_t> kWindowInitFlags = {
            0x00000020, 0x00004000};
        extern objects::Window *createWindow(
            int height, int width, const char *title,
            std::vector<uint32_t> flags = kWindowInitFlags);
    } // namespace sdl
};    // namespace window
