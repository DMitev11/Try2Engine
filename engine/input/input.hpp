#pragma once
#include "input_misc.h"
namespace input {
    /**
     * @brief Create an InputSystem object to initialize and
     * poll input from
     *
     * @tparam Args variadic, based on the library/libraries
     * used to create input poll
     * @return InputSystem* which should poll input from
     * input devices
     */
    template <typename... Args>
    static InputSystem *createInputSystem(Args...);
} // namespace input

#ifdef USE_SDL
#include "sdl_input.h"
template <typename... Args>
inline static input::InputSystem *
input::createInputSystem(Args...) {
    auto input = new input::sdl::SdlInputSystem();
    input->init();
    return input;
}
#endif