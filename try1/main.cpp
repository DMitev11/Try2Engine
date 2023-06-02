#include "inc/EventEmitter.h"
#include "initialization/initialization.hpp"
#include "logger/logger.h"
#include "objects/object.h"
#include "render/render.hpp"
#include "window/window.hpp"
using namespace try1;

int main(int argc, char const *argv[]) {
    LOG_CLIENT_INFO("", "asdasdasd");
    // logger::createConsoleSink(
    //     "asdasd", "s",
    //     logger::ConsoleLoggerTypes::kConsole);
    // std::shared_ptr<spdlog::logger> console =
    //     spdlog::stdout_color_mt("console");

    // console->set_pattern("[%l] %n %v (%s)");
    // console->info("hello");
    // SPDLOG_TRACE()
    // std::function<void(int i)> func = [](int i) {
    //     std::cout << 12;
    // };
    // EventEmitter emitter;
    // emitter.On(0, func);
    // emitter.Once(0, func);
    // emitter.Emit<>(0);
    // int i = 0;

    return 0;
}