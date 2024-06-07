#include "libjaltop.hpp"

#include <iostream>

int main() {
    std::cout << jaltop_cpu_usage(0) << ' ' << jaltop_ram_usage() << '\n';
}
