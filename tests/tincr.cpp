#include <string>
#include <vector>
#include <iostream>
#include <nat.hpp>


int main(int argc, char ** argv) {
    std::vector<unsigned> digits;
    for (int i = 1; i < argc; i++) {
        digits.push_back(std::stoul(argv[i]));
    }

    lnum::nat n{digits};
    std::cout << n << std::endl;
    ++n;
    std::cout << n << std::endl;
}
