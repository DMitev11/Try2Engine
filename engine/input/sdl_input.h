#pragma once
#include "input_misc.h"
#include <SDL3/SDL.h>
namespace input {
    namespace sdl {
        /**
         * @brief SDL3-based implementation of the
         * InputSystem
         * @see input_misc.h#InputSystem
         *
         */
        class SdlInputSystem : public InputSystem {
          public:
            ~SdlInputSystem() = default;
            SdlInputSystem() = default;
            void init() override;
            void poll() override;
            void terminate() override;
            void shutdown() override;

          protected:
            /**
             * @brief Initialize and create a controller.
             * Pushed to the inherited controllers vector
             *
             * @param event Event noting that a controller
             * have been connected to the current system
             * @return valid: Controller* (could return an
             * already created controller with the same id),
             * invalid: nullptr
             */
            Controller *addController(SDL_Event event);

            /**
             * @brief Destroy a controller and clean after
             *
             * @param event Event noting that a controller
             * have been been disconnected from the current
             * system
             */
            void removeController(SDL_Event controller);
            /**
             * @see removeController
             *
             * @param index of the controller which should
             * be destroyed manually, and cleaned after
             */
            void removeController(int index);
        };
    }; // namespace sdl
} // namespace input