#include "../engine/window/window.h"
#include "initialization/initialization.h"
#include <iostream>
#include <stdexcept>
int main(int argc, char const *argv[])
{
    if(!Initialization::init(Initialization::DEFAULT_INIT_FLGAS, Initialization::DEFAULT_HINTS)){
       std::string err = "Cannot initialize";
       std::cout<<err;
       throw std::runtime_error(err);
    }
    Window::init();
    /* code */
}
