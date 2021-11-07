#include "main.h"

auto num_log = 0;
void write_log(int l, const char* msg) {
    std::cout << num_log << " level:" << l << " msg:" << msg;
    num_log++;
}

int main() {

	/// https://github.com/PolyMarsDev/Twini-Golf
    auto run_game = std::make_shared<MCore>();
    const auto status = run_game->run();

    return status;
}