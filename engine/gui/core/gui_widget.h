#pragma once
#include <libraries/imgui/imgui.h>
#include <string>
#include <vector>
namespace gui {
    class GuiWidget {
      public:
        GuiWidget(const char *name,
                  std::vector<int> flags = {})
            : name(name), flags(calculateFlags(flags)){};
        virtual ~GuiWidget(){};
        virtual void begin() {
            ImGui::Begin(name, close, flags);
        };
        virtual void end() {
            ImGui::End();
            //@todo fix
            if (*close) {
                delete this;
            }
        };
        virtual void render(){
            // override me
        };
        const char *getName() {
            return std::string(name).c_str();
        }

      protected:
        const char *name;
        const int flags;
        bool *close = new bool(false);

      private:
        static int calculateFlags(std::vector<int> flags) {
            int _flags = 0;
            for (int flag : flags) {
                _flags |= flag;
            }
            return _flags;
        }
    };
} // namespace gui
