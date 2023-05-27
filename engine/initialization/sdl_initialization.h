#pragma once
#include <unordered_map>
#include <vector>
namespace initialization
{
    namespace sdl
    {
        const std::vector<uint32_t> kInitFlags = {0x00000020};
        const std::unordered_map<const char *, const char *> kInitHints = {{"SDL_HINT_RENDER_SCALE_QUALITY", "1"}};
        const std::vector<uint32_t> kImageInitFlags = {0x00000001, 0x00000002};

        extern bool
        Init(std::vector<uint32_t> initFlags = kInitFlags, const std::unordered_map<const char *, const char *> hints = kInitHints,
             std::vector<uint32_t> imgFlags = kImageInitFlags);
    }; // namespace sdl
} // namespace initialization
