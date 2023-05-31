#include "inc/EventEmitter.h"
#include "initialization/initialization.hpp"
#include "objects/object.h"
#include "render/render.hpp"
#include "window/window.hpp"
#include <SDL3/SDL.h>
int tickRate = 1;
using namespace try1;
int main(int argc, char const *argv[]) {
    // initialization::Init();
    // objects::Window *window =
    //     window::CreateWindow(1000, 1000, "test");
    // objects::Renderer *renderer =
    //     render::CreateRenderer(window);

    EventEmitter emitter;
    std::function<void(int i)> func = [](int i) {
        std::cout << 12;
    };
    emitter.On(0, func);
    emitter.Once(0, func);
    emitter.Emit<>(0);
    int i = 0;
    // input->Emit(0);
    // input->Emit(1);
    // InputSystem *input = new InputSystem();
    // input->PollInput();
    // while (true) {
    //     tickRate++;
    // };

    return 0;
}
