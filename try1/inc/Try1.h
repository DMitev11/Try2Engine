#pragma once
#include "utils/entry.h"
namespace try1 {
    class Try1 : public utils::Entry {
      public:
        Try1();
        ~Try1() override;
        void run() override;
    };
} // namespace try1