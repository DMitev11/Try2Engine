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

        const std::string getName() const {
            return std::string(kName);
        };

      protected:
        Layer(const char *kName = "Layer") : kName(kName) {}
        virtual ~Layer(){};
        Layer(const Layer &) = default;
        Layer(Layer &&) = delete;
        const char *kName;

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