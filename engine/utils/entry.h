#pragma once
#include "layer_stack.h"
namespace utils {
    class Entry {
      public:
        Entry() = default;
        virtual ~Entry(){

        };
        virtual void run() = 0;

      protected:
        LayerStack layerStack;
    };
} // namespace utils