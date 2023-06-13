#pragma once
#include "../core/gui_widget.h"

namespace gui {
    class ExampleWidget : public GuiWidget {
      public:
        ExampleWidget(const char *name,
                      std::vector<int> flags = {})
            : GuiWidget(name, flags) {}
        ~ExampleWidget() override{};

        void render() override;
    };
} // namespace gui