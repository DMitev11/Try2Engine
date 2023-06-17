#include <gui/core/gui_layer.h>
#include <gui/widgets/example_widget.h>
#include <inc/GameLayer.h>
#include <inc/Try1.h>
#include <input/input.hpp>
#include <loader/loader.hpp>
#include <logger/logger.h>
#include <render/render.hpp>
#include <sdl_window_object.h>
#include <window/window.hpp>
using namespace try1;
Try1::Try1(){

};
void Try1::run() {
    window::init();
    render::init();
    auto window =
        window::createWindow(1000, 1200, "GuiWindow");
    auto renderer = render::createRenderer(window);
    auto inputSystem = input::createInputSystem();
    inputSystem->init();

    auto game =
        this->layerStack.addLayer(new try1::GameLayer(
            "GameLayer", renderer, inputSystem));

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
        std::function(
            [&](int i, input::InputSystem *input) {
                exit = true;
            }));
    while (!exit) {
        inputSystem->poll();
        render::setDrawColor(renderer, 255, 0, 0, 255);
        this->layerStack.tick(0.005f);
        render::renderFrame(renderer);
        render::clearRenderer(renderer);
    }
    this->layerStack.shutdown();
    render::terminate(renderer);
    window::terminate(window);
    render::shutdown();
    window::shutdown();
};
Try1::~Try1(){};