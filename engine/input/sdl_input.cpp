#include "input_misc.h"
#include "sdl_input.h"
#include <logger/logger.h>  
#include <cstdlib>
#include <string>
using namespace input;

void sdl::SdlInputSystem::init() {
    if (SDL_Init(SDL_INIT_GAMEPAD) < 0) {
        LOG_ENGINE_ERROR("SDL could not initialize! SDL_Error: ", SDL_GetError());
        return;
    }
}
void sdl::SdlInputSystem::poll() {
    SDL_Event event;
    SDL_PollEvent(&event);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            //Critical error detected c0000374

        case SDL_EVENT_GAMEPAD_ADDED: {
            LOG_ENGINE_INFO("InputSystem: ", "Gamepad just connected");
            this->addController(event);
            break;
        }
        case SDL_EVENT_GAMEPAD_REMOVED: {
            LOG_ENGINE_INFO("InputSystem: ", "Gamepad just disconnected");
            this->removeController(event);
            break;
        }
        case  SDL_EVENT_GAMEPAD_BUTTON_DOWN: {
            int id = event.gdevice.which;
            auto it = std::find_if(activeControllers.begin(), activeControllers.end(),
                [id](const Controller* controller) {
                    return controller->id == id;
                }
            );
            if (it != activeControllers.end()) {
                Controller* controller = *it;
                controller->eventEmitter.Emit(kEventGamepadDown, event.gbutton);
            }
            break;
        }
        case  SDL_EVENT_GAMEPAD_BUTTON_UP: {
            int id = event.gdevice.which;
            auto it = std::find_if(activeControllers.begin(), activeControllers.end(),
                [id](const Controller* controller) {
                    return controller->id == id;
                }
            );
            if (it != activeControllers.end()) {
                Controller* controller = *it;
                controller->eventEmitter.Emit(kEventGamepadDown, event.gbutton);
            }
            break;
        }
        case  SDL_EVENT_GAMEPAD_AXIS_MOTION: {
            int id = event.gdevice.which;
            auto it = std::find_if(activeControllers.begin(), activeControllers.end(),
                [id](const Controller* controller) {
                    return controller->id == id;
                }
            );
            if (it != activeControllers.end()) {
                Controller* controller = *it;
                controller->eventEmitter.Emit(kEventGamepadDown, event.gaxis);
            }
            break;
        }


        case SDL_EVENT_KEY_DOWN: {
            this->eventEmitter.Emit(
                InputEvents::kEventKeyboardDown,
                event.key.keysym.sym);
            break;
        }
        case SDL_EVENT_KEY_UP: {
            this->eventEmitter.Emit(
                InputEvents::kEventKeyboardUp,
                event.key.keysym.sym);
            break;
        }
        case SDL_EVENT_MOUSE_MOTION: {
            this->eventEmitter.Emit(
                InputEvents::kEventMousePointer,
                event.motion);
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            this->eventEmitter.Emit(
                InputEvents::kEventMouseDown, event.button);
            break;
        }
        case SDL_EVENT_MOUSE_BUTTON_UP: {
            this->eventEmitter.Emit(
                InputEvents::kEventMouseUp, event.button);
            break;
        }
        }
    }
}

Controller* sdl::SdlInputSystem::addController(SDL_Event event) {
    int controllerId = event.gdevice.which;
    LOG_ENGINE_INFO("InputSystem: ", (std::string("Controller") + std::to_string(controllerId)).c_str());
    for (Controller* controller : activeControllers) {
        if (controller->id == controllerId) {
            LOG_ENGINE_WARN("InputSystem: ", (std::string("Controller") + std::to_string(controllerId) + std::string(" already joined")).c_str());
            return controller;
        }
    }
    SDL_Gamepad* controller = SDL_OpenGamepad(controllerId);
    return new Controller(controllerId, controller);
}

void sdl::SdlInputSystem::removeController(SDL_Event event) {
    int controllerId = event.gdevice.which;
    LOG_ENGINE_INFO("InputSystem: ", (std::string("Controller") + std::to_string(controllerId)).c_str());
    for (int i = 0; i < activeControllers.size(); i++) {
        if (activeControllers[i]->id == controllerId) {
            delete activeControllers[i];
            activeControllers.erase(activeControllers.begin() + i);
            return;
        }
    }
    LOG_ENGINE_WARN("InputSystem: ", (std::string("Controller") + std::to_string(controllerId) + std::string(" is not joined")).c_str());
    return;
}

void sdl::SdlInputSystem::removeController(int index) {
    if (index < 0 || index >= activeControllers.size()) {
        LOG_ENGINE_WARN("InputSystem: ", (std::string("Controller ") + std::to_string(index) + std::string(" does not exist")).c_str());
        return;
    }
    LOG_ENGINE_INFO("InputSystem: ", (std::string("Controller") + std::to_string(index)).c_str());
    delete activeControllers[index];
    activeControllers.erase(activeControllers.begin() + index);
    return;
}