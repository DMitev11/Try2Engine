#include <gui/core/gui_layer.h>
#include <gui/widgets/example_widget.h>
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
    auto inputSystem = input::createInputSystem();
    inputSystem->init();
    auto window =
        window::createWindow(1000, 1000, "GuiWindow");
    auto window2 =
        static_cast<objects::SDLWindow *>(window);
    auto renderer = render::CreateRenderer(window);
    auto config = loader::LoadingTextureConfig();
    config.colorKey.r = 0, config.colorKey.g = 0,
    config.colorKey.b = 0;
    auto texture = loader::loadTexture(
        renderer, "assets/rnd.png", config);

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

    std::function<void(uint8_t i)> emitMessage =
        [](uint8_t i) {
            LOG_CLIENT_INFO("Try1: Gamepad Button Down ",
                            std::to_string(i).c_str());
        };

    // Handle gamepad connected via binding gamepad input
    std::function<void(uint8_t id)>
        handleControllerConnect = [&](uint8_t id) {
            LOG_CLIENT_INFO("Try1: Hook Gamepad",
                            std::to_string(id).c_str());
            auto controller =
                inputSystem->getController(id);
            inputSystem->getController(id)->eventEmitter.On(
                input::kEventGamepadDown, emitMessage);
        };

    // Hook gamepad created
    inputSystem->getEmitter()->On(
        input::kEventGamepadCreated,
        handleControllerConnect);

    bool exit = false;
    inputSystem->getEmitter()->On(
        input::kEventQuit,
        std::function([&](int i) { exit = true; }));
    while (!exit) {
        inputSystem->poll();
        render::SetDrawColor(renderer, 255, 0, 0, 255);
        render::RenderAsset(renderer, texture, 0, 0);

        this->layerStack.tick(1);
        render::RenderFrame(renderer);
        render::ClearRender(renderer);
    }
    this->layerStack.removeLayer("try1");
};
Try1::~Try1(){};