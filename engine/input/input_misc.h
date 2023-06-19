#pragma once
#include "utils/event_emitter.hpp"
namespace input {

    /**
     * @brief Clarification that each input event should be
     * int
     *
     */
    typedef int KeyCode;

    /**
     * @brief Based on available input devices for a game or
     * an application.
     * @note Will expand in the future
     * @warning Use enum rather than just an int, as order
     * could change => key value will change
     *
     */
    enum InputEvents : KeyCode {
        kEventKeyboardDown,
        kEventKeyboardUp,
        kEventMousePointer,
        kEventMouseDown,
        kEventMouseUp,
        kEventGamepadAxis,
        kEventGamepadDown,
        kEventGamepadUp,
        kEventGamepadCreated,
        kEventQuit
    };

    /**
     * @brief Instance of a created and connected
     * gamepad/controller
     *
     */
    struct Controller {
        inline Controller(int kId, void *input)
            : kId(kId), input(input) {}
        utils::EventEmitter eventEmitter;
        const int kId;
        void *input;
    };

    /**
     * @brief Separate instances of created input systems
     * with different origin should be allowed. \n Emits
     * events on detected implemented input from input
     * devices
     *
     * @warning Contains intances of connected controllers
     * which need to be destroyed, deleted and cleaned up
     * before a `terminate` of each system
     *
     */
    class InputSystem {
      public:
        ~InputSystem() = default;
        InputSystem() = default;

        /**
         * @brief Initialize library/libraries used to poll
         * input, based on the implementation
         *
         */
        virtual void init(){
            // override me
        };

        /**
         * @brief Run each frame on a separate thread
         *
         */
        virtual void poll(){
            // override me
        };

        /**
         * @brief Terminate current input system instance
         *
         */
        virtual void terminate(){
            // override me
        };

        /**
         * @brief Shutdown all libraries related to this
         * implementation of the input system
         * @warning Do not call this method until all
         * instances of the current implementation haven't
         * been terminate - otherwise could lead to
         * undefined and unhandled behaviour
         *
         */
        virtual void shutdown(){
            // override me
        };

        /**
         * @brief Retrieve a pointer of the event emitter
         * @warning Changes on the member variables of the
         * emitter are not permitted, externally
         *
         *
         * @return utils::EventEmitter* const
         */
        utils::EventEmitter *const getEmitter() {
            return &this->eventEmitter;
        };

        /**
         * @brief Get a pointer to one of the connected
         * controllers to this input system
         * @note Input events of that controller
         *
         * @param kId of the controller
         * @return valid: Controller* const \n invalid:
         * nullptr
         */
        Controller *const getController(int id) {
            for (auto controller :
                 this->activeControllers) {
                if (controller->kId == id)
                    return controller;
            }
            return nullptr;
        };

      protected:
        /**
         * @brief Retrieve a pointer of the event emitter
         * @note Controller creation, controller removal,
         * mouse and keyboard events
         * @warning Changes on the member variables of the
         * emitter are not permitted, externally
         *
         *
         * @return utils::EventEmitter* const
         */
        utils::EventEmitter eventEmitter;
        std::vector<Controller *> activeControllers;
    };

} // namespace input