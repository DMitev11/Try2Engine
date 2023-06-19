#pragma once
#include <libraries/imgui/imgui.h>
#include <string>
#include <vector>
namespace gui {
    /**
     * @brief Widgets /n Based on "ImGui" windows
     *
     * @note Override with all necessary logic for a
     * widget(member variables, methods etc.) and most
     * importantly 'render()' -
     *
     * @warning This class should be abstracted to an
     * adapter class, as GUI could be implemented based on
     * other libraries than "ImGui" only
     */
    class GuiWidget {
      public:
        GuiWidget(const char *name,
                  std::vector<int> flags = {})
            : kName(name), flags(calculateFlags(flags)){};
        virtual ~GuiWidget(){};

        /**
         * @brief Call it to buffer this widget/window for
         * the next frame
         * @note Before "render()"
         */
        virtual void begin() {
            ImGui::Begin(kName, close, flags);
        };

        /**
         * @brief Call it to stop appending new elements to
         * the widget/window
         * @note After "render()"
         */
        virtual void end() {
            ImGui::End();
            //@todo fix - doesn't change
            if (*close) {
                delete this;
            }
        };

        /**
         * @brief Override to present which elements
         * should be rendered in this widget/window, and if
         * there should be any logic bound to changes in
         * those elements (radio button being clicked,
         * slider moved etc.)
         *
         * @see "gui::ExampleWidget"
         */
        virtual void render(){
            // override me
        };
        const char *getName() {
            return std::string(kName).c_str();
        }

      protected:
        const char *kName;
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
