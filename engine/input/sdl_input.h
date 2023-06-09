#pragma once
#include "input_misc.h"
#include <SDL3/SDL.h>
namespace input {
    namespace sdl {
        class SdlInputSystem: public InputSystem {
        public:
            ~SdlInputSystem() = default;
            SdlInputSystem() = default;
            void init() override;
            void poll() override;
        protected:
            Controller* addController(SDL_Event event);
            void removeController(SDL_Event controller);
            void removeController(int index);
        };
    };
}