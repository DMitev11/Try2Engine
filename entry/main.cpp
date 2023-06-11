#include <utils/entry_point.h>

int main() {
    utils::Entry *point = utils::createEntryPoint();
    point->Run();
    /* code */
    return 0;
}
