#pragma once
#include "EventEmitter.h"

namespace try1 {
    typedef int KeyCode;
    enum InputTypes {
        kKeyboardButton,
        kMouseClick,
        kMouseLocation
    };

    class InputSystem {
      public:
        ~InputSystem() = default;
        InputSystem() = default;
        void Init();
        void PollInput();
        void HandleEscape();

      private:
        void EmitEvent(int event);

        EventEmitter eventEmitter;
    };
} // namespace try1