#include <gui/core/gui_layer.h>
#include <gui/widgets/example_widget.h>
#include <inc/Try1.h>
#include <input/input.hpp>
#include <render/render.hpp>
#include <sdl_window_object.h>
#include <window/window.hpp>
using namespace try1;
Try1::Try1(){

};
void Try1::run() {
    window::init();
    render::init();
    auto inputSystem = input::createInputSystem();
    inputSystem->init();
    auto window =
        window::createWindow(1000, 1000, "GuiWindow");
    auto window2 =
        static_cast<objects::SDLWindow *>(window);
    auto renderer = render::CreateRenderer(window);
    auto gui = static_cast<gui::GuiLayer *>(
        this->layerStack.addLayer(
            new gui::GuiLayer("GuiLayer", renderer)));
    gui->addWidget(
        new gui::ExampleWidget("example widget"));
    gui->addWidget(
        new gui::ExampleWidget("example widget3"));
    gui->addWidget(
        new gui::ExampleWidget("example widget4"));
    gui->addWidget(
        new gui::ExampleWidget("example widget2"));
    bool exit = false;
    inputSystem->getEmitter()->On(
        input::kEventQuit,
        std::function([&](int i) { exit = true; }));
    while (!exit) {
        inputSystem->poll();
        this->layerStack.tick(1);
        render::SetDrawColor(renderer, 255, 0, 0, 255);
        render::RenderFrame(renderer);
        render::ClearRender(renderer);
    }
    this->layerStack.removeLayer("try1");
};
Try1::~Try1(){};