#pragma once
#include "loop.h"
#include <string>
namespace utils {

    /**
     * @brief A layer, member of layer stack
     *
     */
    class Layer : public LayerComponent {
      public:
        virtual void onAttach(){};
        virtual void onDetach(){};
        virtual void onTick(float delta){};

        const std::string getName() {
            return std::string(name);
        };

      protected:
        Layer(const char *name = "Layer") : name(name) {}
        virtual ~Layer(){};
        Layer(const Layer &) = default;
        Layer(Layer &&) = delete;
        const char *name;

        /**
         * @brief Only a LayerStack should be able to create
         * and contain a layer
         * @note As a `utils::Entry` is a friend of
         * `utils::LayerStack`, entries could create layers
         * and add them to a LayerStack
         *
         */
        friend class LayerStack;
    };
} // namespace utils