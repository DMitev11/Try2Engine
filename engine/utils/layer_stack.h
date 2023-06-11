#pragma once
#include "layer.h"
#include <vector>
namespace utils {
    class LayerStack {
      public:
        LayerStack() = default;

        Layer *addLayer(Layer *);
        void removeLayer(const char *name);

        void init();
        void tick(float delta);
        void shutdown();

      private:
        ~LayerStack(){};
        std::vector<Layer *> layers;

        // LayerStack(LayerStack &const) = delete; //C4227
        LayerStack(LayerStack &) = delete;
        LayerStack(LayerStack &&) = delete;

        friend class Entry;
    };
} // namespace utils