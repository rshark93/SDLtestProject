#include "main.h"

auto num_log = 0;
void write_log(int l, const char* msg) {
    std::cout << num_log << " level:" << l << " msg:" << msg;
    num_log++;
}

int main() {

    auto runGame = new MCore();
    auto status = runGame->run();
    delete runGame;

    //WidgetContainer *wdgC = new WidgetContainer();
    //Image *img = new Image();
    //Button* button = new Button();

    //delete button;
    //delete img;
    //delete wdgC;

    return status;
}