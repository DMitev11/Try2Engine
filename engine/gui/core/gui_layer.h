#pragma once
#include "gui_widget.h"
#include <renderer_object.h>
#include <utils/layer.h>
namespace gui {
    class GuiLayer : public utils::Layer {
      public:
        GuiLayer(const char *name,
                 objects::Renderer *renderer)
            : utils::Layer(name), renderer(renderer){

                                  };
        ~GuiLayer() override{};

        void onAttach() override;
        void onDetach() override;
        void onTick(float delta) override;

        GuiWidget *addWidget(GuiWidget *widget);
        //@todo replace with id
        void removeWidget(const char *name);
        void begin();
        void render();
        void end();

      protected:
        objects::Renderer *renderer;
        std::vector<GuiWidget *> widgets;
    };
} // namespace gui