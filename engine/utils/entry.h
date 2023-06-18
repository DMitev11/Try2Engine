#pragma once
#include "layer_stack.h"
namespace utils {
    /**
     * @brief Entry point of an application
     * @note All implementations of this class should handle
     * their runtime. \n End of `run` should end the
     * lifetime of the running applicatioin
     *
     */
    class Entry {
      public:
        Entry() = default;
        virtual ~Entry(){};

        /**
         * @brief All continous logic of this `Entry`
         *
         */
        virtual void run() = 0;

      protected:
        /**
         * @brief An application should be able to run
         * several layers at oncem and call their events
         * consecutively
         * @see utils::LayerStack
         *
         */
        LayerStack layerStack;
    };
} // namespace utils