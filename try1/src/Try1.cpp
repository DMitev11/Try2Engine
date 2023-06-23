#include <chrono>
#include <gui/core/gui_layer.h>
#include <gui/widgets/example_widget.h>
#include <inc/ControllerWidget.h>
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
    loader::init();
    auto window =
        window::createWindow(1000, 1200, "GuiWindow");
    auto renderer = render::createRenderer(window);
    auto inputSystem = input::createInputSystem();
    inputSystem->init();

    auto gameData = new GameData();
    auto game = static_cast<try1::GameLayer *>(
        this->layerStack.addLayer(new try1::GameLayer(
            "GameLayer", renderer, inputSystem, gameData,
            1200)));

    auto gui = static_cast<gui::GuiLayer *>(
        this->layerStack.addLayer(
            new gui::GuiLayer("GuiLayer", renderer)));

    auto widget =
        new ControllerWidget(gameData, "ControllerWidget");
    gui->addWidget(widget);
    widget->getEmitter()->On(
        ControllerWidget::Events::kFire,
        std::function([&](uint32_t i) { game->fire(); }));

    bool exit = false;
    inputSystem->getEmitter()->On(
        input::kEventQuit,
        std::function([&](int i) { exit = true; }));

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    ;
    while (!exit) {
        end = std::chrono::high_resolution_clock::now();
        float elapsed =
            std::chrono::duration_cast<
                std::chrono::milliseconds>(end - start)
                .count();
        start = std::chrono::high_resolution_clock::now();
        render::clearRenderer(renderer);
        inputSystem->poll();
        render::setDrawColor(renderer, 255, 0, 0, 255);

        this->layerStack.tick(elapsed);
        render::renderFrame(renderer);
    }
    this->layerStack.shutdown();
    render::terminate(renderer);
    window::terminate(window);
    render::shutdown();
    window::shutdown();
};
Try1::~Try1(){};