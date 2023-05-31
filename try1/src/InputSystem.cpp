#include "inc/InputSystem.h"
#include <SDL3/SDL.h>
using namespace try1;
void InputSystem::Init() {
    // do something
}
// continous
void InputSystem::PollInput() {
    SDL_Event event;
    SDL_PollEvent(&event);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_KEY_DOWN: {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                // DispatchEvent<int>(
                // InputTypes::kKeyboardButton,
                // static_cast<int>(event.key.keysym.sym));
            }
        }
        }
    }
}
void InputSystem::EmitEvent(int event) {
    this->eventEmitter.Emit(event);
}