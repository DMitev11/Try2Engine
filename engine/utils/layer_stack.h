#pragma once
#include "layer.h"
#include "loop.h"
#include <vector>
namespace utils {

    /**
     * @brief Controlling stack for layers. \n Calls
     * LayerComponent events:
     * - OnAttach, when a layer can been created and
     * attached to the current layer stack
     * - OnTick, during each tick update of the layer stack
     * - OnDetach, when a layer have been removed from the
     * layer stack
     *
     * This class follows LoopEvents modal, present in most
     * game-related applications/simulations:
     *
     * - init - initialization logic for the current layer
     * stack, if there is initialization logic necessary
     * specifically for this layer stack (initialize
     * libraries, add specific layers etc)
     *
     * - tick - on every successful loop of the program
     *
     * - shutdown - called once the application is about to
     * end
     *
     * @warning If project's structure have been changed to
     * include several layer stacks - override 'terminate'
     * as a method to destroy and clear a single layer stack
     *
     */
    class LayerStack : public LoopEvents {
      public:
        Layer *addLayer(Layer *);
        void removeLayer(const char *name);

        void init() override;
        void tick(float delta) override;
        void shutdown() override;

      private:
        LayerStack() = default;
        ~LayerStack(){};

        /**
         * @brief Sequence of layers matters
         * 0 - would update and render first
         * last - would update and render on top of
         * everything else
         *
         */
        std::vector<Layer *> layers;

        // LayerStack(LayerStack &const) = delete; //C4227
        LayerStack(LayerStack &) = delete;
        LayerStack(LayerStack &&) = delete;

        /**
         * @brief Only `Entry` points of each application
         * should be able to create a layer stack.
         *
         * @warning Layer stacks in layer stacks are highly
         * inadvisable - could lead to very complicated and
         * heavy logic load to update in a tick
         */
        friend class Entry;
    };
} // namespace utils