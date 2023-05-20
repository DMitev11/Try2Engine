#pragma once 
#include <string>
namespace objects {
    class Window {
    public:
        ~Window() = default;
        int height;
        int width;
        std::string title;

    protected:
        Window(int height, int width, std::string title) {
            this->height = height;
            this->width = width;
            this->title = title;
        }
    };
}