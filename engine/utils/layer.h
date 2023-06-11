#pragma once
#include <string>
namespace utils {
    class Layer {
      public:
        Layer(const char *name = "Layer") {}
        ~Layer() = default;

        virtual void onAttach();
        virtual void onDetach();
        virtual void onTick(float delta);

        const std::string &getName() { return name; };

      private:
        Layer(const Layer &) = delete;
        Layer(Layer &&) = delete;

        const char *name;
    };
} // namespace utils