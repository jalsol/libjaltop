#include "libjaltop.hpp"

#include <iostream>

int main() {
    for (;;) {
        std::cout << jaltop_cpu_percentage(1000)
                  << ' '
                  << jaltop_ram_percentage()
                  << '\n';
    }
}
