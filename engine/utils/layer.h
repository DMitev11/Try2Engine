#pragma once
#include <string>
namespace utils {
    class Layer {
      public:
        Layer(const char *name = "Layer") : name(name) {}
        virtual ~Layer(){};

        virtual void onAttach(){};
        virtual void onDetach(){};
        virtual void onTick(float delta){};

        const std::string getName() {
            return std::string(name);
        };

      protected:
        const char *name;
        Layer(const Layer &) = default;
        Layer(Layer &&) = delete;
        friend class LayerStack;
    };
} // namespace utils