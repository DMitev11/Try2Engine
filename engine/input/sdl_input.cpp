#include "sdl_input.h"
#include "input_misc.h"
#include <cstdlib>
#include <logger/logger.h>
#include <string>

#ifdef USE_IMGUI
#include <libraries/imgui/backends/imgui_impl_sdl3.h>
#endif
using namespace input;

void sdl::SdlInputSystem::init() {
    if (SDL_Init(SDL_INIT_GAMEPAD) < 0) {
        LOG_ENGINE_ERROR(
            "SDL could not initialize! SDL_Error: ",
            SDL_GetError());
        return;
    }
}
void sdl::SdlInputSystem::poll() {
    SDL_Event event;
    SDL_PollEvent(&event);
    // Capture input for ImGui if built with the project
#ifdef USE_IMGUI
    if (ImGui::GetCurrentContext() != nullptr) {
        ImGui_ImplSDL3_ProcessEvent(&event);
    }
#endif
    switch (event.type) {
    case SDL_EVENT_GAMEPAD_ADDED: {
        LOG_ENGINE_INFO("InputSystem: ",
                        "Gamepad just connected");
        this->addController(event);
        break;
    }
    case SDL_EVENT_GAMEPAD_REMOVED: {
        LOG_ENGINE_INFO("InputSystem: ",
                        "Gamepad just disconnected");
        this->removeController(event);
        break;
    }
    case SDL_EVENT_GAMEPAD_BUTTON_UP:
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN: {
        int id = event.gdevice.which;
        auto it = std::find_if(
            activeControllers.begin(),
            activeControllers.end(),
            [id](const Controller *controller) {
                return controller->kId == id;
            });
        if (it != activeControllers.end()) {
            Controller *controller = *it;
            controller->eventEmitter.Emit(
                event.gbutton.state == SDL_PRESSED
                    ? kEventGamepadDown
                    : kEventGamepadUp,
                event.gbutton.button);
        }
        break;
    }
    case SDL_EVENT_GAMEPAD_AXIS_MOTION: {
        int id = event.gdevice.which;
        auto it = std::find_if(
            activeControllers.begin(),
            activeControllers.end(),
            [id](const Controller *controller) {
                return controller->kId == id;
            });
        if (it != activeControllers.end()) {
            Controller *controller = *it;
            controller->eventEmitter.Emit(kEventGamepadAxis,
                                          event.gaxis);
        }
        break;
    }
    case SDL_EVENT_KEY_UP:
    case SDL_EVENT_KEY_DOWN: {
        this->eventEmitter.Emit(
            event.key.state == SDL_PRESSED
                ? input::kEventKeyboardDown
                : input::kEventKeyboardUp,
            event.key.keysym.sym);
        break;
    }
    case SDL_EVENT_MOUSE_MOTION: {
        this->eventEmitter.Emit(
            InputEvents::kEventMousePointer, event.motion);
        break;
    }
    case SDL_EVENT_MOUSE_BUTTON_UP:
    case SDL_EVENT_MOUSE_BUTTON_DOWN: {
        if (event.button.state == SDL_PRESSED) {
            this->eventEmitter.Emit(
                InputEvents::kEventMouseDown,
                event.button.button);
        } else if (event.button.state == SDL_RELEASED) {
            this->eventEmitter.Emit(
                InputEvents::kEventMouseUp,
                event.button.button);
        }
        break;
    }
    case SDL_EVENT_QUIT: {
        this->eventEmitter.Emit(InputEvents::kEventQuit, 0);
        break;
    }
    }
}

Controller *
sdl::SdlInputSystem::addController(SDL_Event event) {
    int controllerId = event.gdevice.which;
    LOG_ENGINE_INFO("InputSystem: ",
                    (std::string("Controller") +
                     std::to_string(controllerId))
                        .c_str());
    for (Controller *controller : activeControllers) {
        if (controller->kId == controllerId) {
            LOG_ENGINE_WARN("InputSystem: ",
                            (std::string("Controller") +
                             std::to_string(controllerId) +
                             std::string(" already joined"))
                                .c_str());
            return controller;
        }
    }
    SDL_Gamepad *controller = SDL_OpenGamepad(controllerId);
    this->activeControllers.push_back(
        new Controller(controllerId, controller));
    this->eventEmitter.Emit(kEventGamepadCreated,
                            controllerId);
    return this
        ->activeControllers[this->activeControllers.size() -
                            1];
}

void sdl::SdlInputSystem::removeController(
    SDL_Event event) {
    int controllerId = event.gdevice.which;
    LOG_ENGINE_INFO("InputSystem: ",
                    (std::string("Controller") +
                     std::to_string(controllerId))
                        .c_str());
    for (int i = 0; i < activeControllers.size(); i++) {
        if (activeControllers[i]->kId == controllerId) {
            delete activeControllers[i];
            activeControllers.erase(
                activeControllers.begin() + i);
            return;
        }
    }
    LOG_ENGINE_WARN("InputSystem: ",
                    (std::string("Controller") +
                     std::to_string(controllerId) +
                     std::string(" is not joined"))
                        .c_str());
    return;
}

void sdl::SdlInputSystem::removeController(int index) {
    if (index < 0 || index >= activeControllers.size()) {
        LOG_ENGINE_WARN("InputSystem: ",
                        (std::string("Controller ") +
                         std::to_string(index) +
                         std::string(" does not exist"))
                            .c_str());
        return;
    }
    LOG_ENGINE_INFO(
        "InputSystem: ",
        (std::string("Controller") + std::to_string(index))
            .c_str());
    delete activeControllers[index];
    activeControllers.erase(activeControllers.begin() +
                            index);
    return;
}

void sdl::SdlInputSystem::terminate() {}
void sdl::SdlInputSystem::shutdown() {
    // Terminate SDL's gamepad input module
    if (SDL_WasInit(SDL_INIT_GAMEPAD) == SDL_INIT_GAMEPAD) {
        SDL_QuitSubSystem(SDL_INIT_GAMEPAD);
    }
    return;
}