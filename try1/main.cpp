#include "utils/event_emitter.hpp"
#include "initialization/initialization.hpp"
#include "logger/logger.h"
#include "input/input.hpp"
#include "objects/object.h"
#include "render/render.hpp"
#include "window/window.hpp"

int main(int argc, char const* argv[]) {
    initialization::init();
    auto window = window::createWindow(1000, 1000, "hello");
    auto input = input::createInputSystem();
    while (true) {
        input->poll();
    }
    return 0;
}