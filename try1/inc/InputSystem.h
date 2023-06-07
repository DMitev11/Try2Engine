#pragma once
#include "EventEmitter.h"
#include <vector>

namespace try1 {
    typedef int KeyCode;
    enum InputTypes {
        kKeyboardButton,
        kMouseClick,
        kMouseLocation
    };

    enum InputKey {
        kBack = 0,
        kAccept = 1,
        kA = 2,
        kB = 3,
        kY = 4,
        kX = 5,
    };
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
        EventEmitter eventEmitter;
        const int id;
        void* input;
        // void pollInput();
        // virtual void refresh();
        // virtual void terminate();
    };
    struct GamepadController: public Controller {
        inline GamepadController(int id, void* input)
            : Controller(id, input) {};
    };

    class InputSystem {
    public:
        ~InputSystem() = default;
        InputSystem() = default;
        void init();
        void poll();

    private:
        template<typename T>
        Controller* addController(T event);
        template<typename T>
        void removeController(T controller);
        EventEmitter eventEmitter;
        std::vector<Controller*> activeControllers;
    };

} // namespace try1