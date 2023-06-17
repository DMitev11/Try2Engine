#pragma once

namespace utils {
    class LoopComponent {
      public:
        LoopComponent(){};
        virtual ~LoopComponent() = default;

        virtual void init(){};
        virtual void tick(float delta){};
        virtual void terminate(){};
        virtual void shutdown(){};
    };
} // namespace utils