#include <iostream>
#include <stdexcept>

#include "engine/initialization/initialization.hpp"
#include "engine/window/window.hpp"
int
main(int argc, char const *argv[])
{
    if (!initialization::init(initialization::DEFAULT_INIT_FLAGS, initialization::DEFAULT_HINTS))
    {
        std::string err = "Cannot initialize";
        std::cout << err;
        throw std::runtime_error(err);
    }
    window::createWindow(1000, 1000, "Try2Engine Application", window::DEFAULT_WINDOW_INIT_FLAGS);
    /* code */
};