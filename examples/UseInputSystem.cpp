#include <input/input.hpp>
#include <window/window.hpp>
int main(int argc, char const *argv[]) {
    // 0. Create a window to bind the input to
    window::init();
    auto window =
        window::createWindow(1000, 1000, "Input Example");
    // 1. Create an input system
    input::InputSystem *input = input::createInputSystem();
    // 2.1. Retrieve a pointer to the event emitter of the
    // input system
    auto emitter = input->getEmitter();
    // 2.2. Bind an std::function<lambda()> to an emitted
    // event from the input system
    // Bind on keyboard button down
    emitter->On(
        input::kEventMouseDown,
        std::function<void(int32_t)>([](int32_t buttonId) {
            LOG_CLIENT_INFO(
                std::to_string(buttonId).c_str(),
                "KEYBOARD BUTTON HAVE BEEN PRESSED");
        }));
    // Bind on gamepad connected
    emitter->On(
        input::kEventGamepadCreated,
        std::function<void(int32_t)>(
            [](int32_t controllerId) {
                LOG_CLIENT_INFO(
                    std::to_string(controllerId).c_str(),
                    "Controller Connected");
            }));

    // Bind clicking quit button
    bool exit = false;
    emitter->On(input::kEventQuit,
                std::function<void(int32_t)>(
                    [&](int32_t id) { exit = true; }));
    while (!exit) {
        // 3. Poll input
        input->poll();
    }
    // 4. Terminate the input system
    input->terminate();
}