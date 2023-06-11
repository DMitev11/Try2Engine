
// #include <logger/logger.h>
// #include <utils/entry_point.h>
// WinMain

#include <utils/entry_point.h>

#include <input/input.hpp>
#include <render/render.hpp>
#include <window/window.hpp>

class PlaceholderEntry : public utils::Entry {

  public:
    PlaceholderEntry(){

    };

    ~PlaceholderEntry(){

    };
    void Run() override {
        window::init();
        auto window =
            window::createWindow(1000, 1000, "try1");
        render::init();
        auto renderer = render::CreateRenderer(window);
        auto input = input::createInputSystem();
        input->init();

        bool close = false;
        input->getEmitter()->On(
            input::kEventQuit,
            std::function([&](int i) { close = true; }));
        while (!close) {
            input->poll();
            render::ClearRender(renderer);
            render::SetDrawColor(renderer, 155, 0, 0, 255);

            render::RenderFrame(renderer);
        }
        input->terminate();
        input->shutdown();
        render::terminate(renderer);
        window::terminate(window);
        render::shutdown();
        window::shutdown();
    };
};

utils::Entry *utils::createEntryPoint() {
    return new PlaceholderEntry();
}