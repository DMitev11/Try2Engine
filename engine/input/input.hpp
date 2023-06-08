#pragma once 
#include "input_misc.h"
namespace input {
    template<typename... Args>
    static InputSystem* createInputSystem(Args...);
}

#ifdef SDL_USED
#include "sdl_input.h"
template<typename... Args>
inline static input::InputSystem* input::createInputSystem(Args...) {
    auto input = new input::sdl::SdlInputSystem();
    input->init();
    return input;
}
#endif