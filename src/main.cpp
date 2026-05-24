#include "Manager.hpp"
#include <iostream>

int main() {
    std::cout << "Starting Temperature Monitor...\n";

    Manager manager("0.0.0.0", 8080);
    manager.mainloop();

    return 0;
}
