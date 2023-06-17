#include "inc/Try1.h"
int main(int argc, char const *argv[]) {
    auto app = new try1::Try1();
    app->run();
    delete app;
    return 0;
}