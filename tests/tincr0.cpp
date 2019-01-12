#include <string>
#include <vector>
#include <iostream>
#include <nat.hpp>
#include <limits>

constexpr unsigned long ulong_max = std::numeric_limits<unsigned long>::max();


int main(int argc, char ** argv) {
    std::vector<unsigned long> digits;
    int i{};
    if (argc > 1) {
        i = std::stoi(argv[1]);
    }
    
    do {
        digits.push_back(ulong_max);
    }    while (i-- > 0);
    // for (int i = 1; i < argc; i++) {
    //     digits.push_back(std::stoul(argv[i]));
    // }

    lnum::nat n{digits};
    std::cout << n << std::endl;
    ++n;
    std::cout << n << std::endl;
}
