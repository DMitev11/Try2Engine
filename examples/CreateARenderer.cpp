#include <loader/loader.hpp>
#include <render/render.hpp>
#include <window/window.hpp>

int main(int argc, char const *argv[]) {
    // 0. Initialize windowing - parameter list based on the
    // implementation. Check build generative flags (CMake
    // flags) in the README.md
    window::init();
    // 0.5. Create a window
    auto window = window::createWindow(1000, 1000, "try1");
    // 2. Initialize rendering - flags available based on
    // the implementation. Check build generative flags
    // (CMake flags) in the README.md
    render::init();
    auto renderer = render::createRenderer(window);
    // 3. Set clear color to draw blank screen
    render::setDrawColor(renderer, 155, 0, 0, 255);
    // 4. (Optional) Buffer an asset for rendering, x: 0 and
    // y: 0
    render::renderAsset(
        renderer,
        loader::loadTexture(renderer, "/assets/box.png"), 0,
        0);
    // 5. Render buffered
    render::renderFrame(renderer);
    // 6. Clear frame
    render::clearRenderer(renderer);
    // 6. Terminate/Destroy a renderer
    render::terminate(renderer);
    // 7. Shutdown rendering implementation when all
    // renderers are finished
    render::shutdown();
}