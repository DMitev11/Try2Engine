#include <loader/loader.hpp>
#include <render/render.hpp>
#include <window/window.hpp>

int main(int argc, char const *argv[]) {
    // 0. Create a window and create a renderer
    window::init();
    render::init();
    auto window = window::createWindow(1000, 1000, "try1");
    auto renderer = render::createRenderer(window);
    // 1. Initialize loader - parameter list based on the
    // implementation.
    // Check implementations.
    // Check build generative flags (CMake flags) in the
    // README.md
    loader::init();

    // 1.a Load a file based on a path
    loader::loadTexture(renderer, "/assets/box.png");
    // 1.b Load a file based on a path and a configuration
    // setup (only color key for now)
    auto config = loader::LoadingTextureConfig();
    config.colorKey.r = 0, config.colorKey.g = 0,
    config.colorKey.b = 0;
    loader::loadTexture(renderer, "/assets/box.png");
}