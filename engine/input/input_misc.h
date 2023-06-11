#pragma once
#include "utils/event_emitter.hpp"
namespace input {

    typedef int KeyCode;

    enum InputEvents {
        kEventKeyboardDown,
        kEventKeyboardUp,
        kEventMousePointer,
        kEventMouseDown,
        kEventMouseUp,
        kEventGamepadDown,
        kEventGamepadCreated,
        kEventQuit
    };
    struct Controller {
        inline Controller(int id, void *input)
            : id(id), input(input) {}
        utils::EventEmitter eventEmitter;
        const int id;
        void *input;
    };

    class InputSystem {
      public:
        ~InputSystem() = default;
        InputSystem() = default;
        virtual void init(){
            // override me
        };
        virtual void poll(){
            // override me
        };
        virtual void terminate(){
            // override me
        };
        virtual void shutdown(){
            // override me
        };

        utils::EventEmitter *const getEmitter() {
            return &this->eventEmitter;
        };
        Controller *const getController(int id) {
            for (auto controller :
                 this->activeControllers) {
                if (controller->id == id)
                    return controller;
            }
            return nullptr;
        };

      protected:
        utils::EventEmitter eventEmitter;
        std::vector<Controller *> activeControllers;
    };

} // namespace input