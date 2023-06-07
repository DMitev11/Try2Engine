#include "inc/InputSystem.h"
#include <SDL3/SDL.h>
#include <cstdlib>
using namespace try1;
void InputSystem::init() {
    // do something
}

// continous
void InputSystem::pollInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_CONTROLLER
            // Key Down
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
        }
        case SDL_EVENT_MOUSE_MOTION: {
            this->eventEmitter.Emit(
                InputEvents::kEventMousePointer,
                event.motion);
        }
        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            this->eventEmitter.Emit(
                InputEvents::kEventMouseDown, event.button);
        }
        case SDL_EVENT_MOUSE_BUTTON_UP: {
            this->eventEmitter.Emit(
                InputEvents::kEventMouseUp, event.button);
        }
            // Controller Button Down
            // Controller Stick
            // Controller Analog triggers
        }
    }
}

// void Controller::pollInput() {

// }
void InputSystem::pollControllers() {}
