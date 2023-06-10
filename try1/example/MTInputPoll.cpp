#include "SDL3/SDL_thread.h"
#include "input/input.hpp"
#include "logger/logger.h"
#include <SDL3/SDL.h>
#include <iostream>
#include <string>
#include <thread>
int main(int argc, char const *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD);
    input::InputSystem *input = input::createInputSystem();

    std::function<void(uint8_t i)> emitMessage =
        [](uint8_t i) {
            LOG_CLIENT_INFO("Try1: Gamepad Button Down",
                            std::to_string(i).c_str());
        };
    std::function<void(uint8_t id)>
        handleControllerConnect = [=](uint8_t id) {
            LOG_CLIENT_INFO("Try1: Hook Gamepad",
                            std::to_string(id).c_str());
            auto controller = input->getController(id);
            input->getController(id)->eventEmitter.On(
                input::kEventGamepadDown, emitMessage);
        };
    input->getEmitter()->On(input::kEventGamepadCreated,
                            handleControllerConnect);
    auto lambda = [](void *data) -> int {
        auto input =
            static_cast<input::InputSystem *>(data);
        while (true) {
            input->poll();
        }
        return 0;
    };
    int returnValue;
    auto thread =
        SDL_CreateThread(lambda, "pollInput", input);
    SDL_WaitThread(thread, &returnValue);
    SDL_Quit();
    return 0;
}