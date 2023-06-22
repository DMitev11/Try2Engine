#include <window/window.hpp>

int main(int argc, char const *argv[]) {
    // 1. Initialize windowing - parameter list based on the
    // implementation. Check build generative flags (CMake
    // flags) in the README.md
    window::init();
    // 2. Create a window
    auto window = window::createWindow(1000, 1000, "try1");
    // 3. Terminate/Destroy a window
    window::terminate(window);
    // 4. Terminate/Destroy windowing library when all
    // windows are done
    window::shutdown();
}