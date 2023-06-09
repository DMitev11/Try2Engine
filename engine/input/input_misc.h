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
        kEventGamepadDown
    };
    struct Controller {
        inline Controller(int id, void* input)
            : id(id), input(input) {}
        utils::EventEmitter eventEmitter;
        const int id;
        void* input;
    };

    class InputSystem {
    public:
        ~InputSystem() = default;
        InputSystem() = default;
        virtual void init() {
            //override me
        };
        virtual void poll() {
            //override me
        };

    protected:
        utils::EventEmitter eventEmitter;
        std::vector<Controller*> activeControllers;
    };

}