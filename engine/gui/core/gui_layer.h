#pragma once
#include "gui_widget.h"
#include <renderer_object.h>
#include <utils/layer.h>

namespace gui {

    /**
     * @brief Graphical User Interface layer.
     * @note Purpose of this layer is to be a collection of
     * widgets, which should render with the same priority.
     * All widgets bound to an instance of this layer should
     * interchange which widget could be on top of another,
     * but all of them should be below the next rendered
     * "Layer"
     *
     * @warning Enforcing widgets (belonging to a layer) to
     * render below all widgets of a layer with higher
     * priority, is to be implemented
     *
     * @warning This class should be abstracted to an
     * adapter class, as GUI could be implemented based on
     * other libraries than "ImGui" only
     */
    class GuiLayer : public utils::Layer {
      public:
        GuiLayer(const char *name,
                 objects::Renderer *renderer)
            : utils::Layer(name), kRenderer(renderer){

                                  };
        ~GuiLayer() override{};

        void onAttach() override;
        void onDetach() override;
        void onTick(float delta) override;

        /**
         * @brief Attach a widget to this layer and call
         * "onAttach"
         *
         * @param widget to be rendered
         * @return GuiWidget*
         * @see gui::GuiWidget
         */
        GuiWidget *addWidget(GuiWidget *widget);

        /**
         * @brief Detach a widget
         *
         * @param name of the widget to remove
         * @warning should be replaced by an unique id, as
         * all widgets should be able to have duplicate
         * names
         */
        void removeWidget(const char *name);

        /**
         * @brief Based on "ImGui". \n Each frame begins
         * with "ImGui" calling "NewFrame"
         */
        void begin();

        /**
         * @brief Render each widget in a sequence
         *
         */
        void render();

        /**
         * @brief Based on "ImGui". \n Each frame begins
         * with "ImGui" calling "EndFrame"
         */
        void end();

      protected:
        /**
         * @brief Which renderer should be used to render
         * all widgets
         */
        objects::Renderer *kRenderer;

        /**
         * @brief All bound widgets
         */
        std::vector<GuiWidget *> widgets;
    };
} // namespace gui