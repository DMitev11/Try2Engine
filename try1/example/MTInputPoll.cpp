#include "SDL3/SDL_thread.h"
#include "input/input.hpp"
#include "logger/logger.h"
#include <iostream>
#include <string>
#include <thread>
#include <window/window.hpp>

int createInputThread(void *data) {

    // Create input system instance
    input::InputSystem *input = input::createInputSystem();

    // Handle gamepad input via emitting a message with the
    // input(button,axis,sensor) id
    std::function<void(uint8_t i)> emitMessage =
        [](uint8_t i) {
            LOG_CLIENT_INFO("Try1: Gamepad Button Down ",
                            std::to_string(i).c_str());
        };

    // Handle gamepad connected via binding gamepad input
    std::function<void(uint8_t id)>
        handleControllerConnect = [=](uint8_t id) {
            LOG_CLIENT_INFO("Try1: Hook Gamepad",
                            std::to_string(id).c_str());
            auto controller = input->getController(id);
            input->getController(id)->eventEmitter.On(
                input::kEventGamepadDown, emitMessage);
        };

    // Hook gamepad created
    input->getEmitter()->On(input::kEventGamepadCreated,
                            handleControllerConnect);

    auto shutdown = static_cast<bool *>(data);
    while (!shutdown) {
        input->poll();
    }
    input->terminate();
    // Shutdown the input system, because its the last entry
    input->shutdown();
    return 0;
}

int main(int argc, char const *argv[]) {
    window::init();
    window::createWindow(1000, 1000, "Multithreaded Input");

    int returnValue;
    bool stop = false;
    auto thread = SDL_CreateThread(createInputThread,
                                   "pollInput", &stop);
    int i = 0;
    while (i < 100) {
        LOG_CLIENT_INFO("Tick #: ",
                        std::to_string(i).c_str());
        i++;
    }
    stop = true;
    SDL_WaitThread(thread, &returnValue);
    SDL_Quit();
    return 0;
}