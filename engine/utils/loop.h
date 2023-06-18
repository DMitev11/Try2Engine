#pragma once

namespace utils {

    /**
     * @brief Based on usual game/simulation runtime events
     */
    class LoopEvents {
      public:
        LoopEvents(){};
        virtual ~LoopEvents() = default;

        /**
         * @brief Called logic specific for the deriving
         * class
         */
        virtual void init(){};
        /**
         * @brief Called on every frame update of the
         * application
         *
         * @param delta time between previous and current
         * frame
         */
        virtual void tick(float delta){};
        /**
         * @brief Called when destroying and cleaning the
         * instance of class which derives from this
         */
        virtual void terminate(){};
        /**
         * @brief On sudden application lifetime
         * termination (user called "Quit" and similar
         * cases)
         */
        virtual void shutdown(){};
    };

    /**
     * @brief Events of instances, members of instances
     * deriving from `utils::LoopEvents`
     *
     * @see utils::LoopEvents
     */
    class LoopComponent {
      public:
        LoopComponent(){};
        virtual ~LoopComponent() = default;

        virtual void onInit(){};
        virtual void onTick(float delta){};
        virtual void onTerminate(){};
        virtual void onShutdown(){};
    };

    /**
     * @brief Events of `Layer
     *
     * @see utils::LoopEvents
     */
    class LayerComponent {
      public:
        LayerComponent(){};
        virtual ~LayerComponent() = default;

        /**
         * @brief Called right after a layer have been
         * attached to a `utils::LayerStack`
         */
        virtual void onAttach(){};

        /**
         * @brief Called when a `utils::LayerStack` update
         * `Tick` is called
         */
        virtual void onTick(float delta){};

        /**
         * @brief Called right before a layer is detached
         * from a `utils::LayerStack`
         */
        virtual void onDetach(){};
    };
} // namespace utils