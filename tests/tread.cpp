#include <string>
#include <vector>
#include <iostream>
#include <nat.hpp>
#include <limits>
#include <sstream>

constexpr unsigned long ulong_max = std::numeric_limits<unsigned long>::max();


void test_input(std::string s) {
    lint::nat n{s};
    std::stringstream outss; outss << n;
    std::string out{outss.str()};

    std::size_t find {s.find_first_not_of('0')};
    if (find != std::string::npos) {
        s.erase(0, find);
    }
    if (s == out) {
        std::cout << "Ok" << std::endl;
    } else {
        std::cerr << "error parsing number" << std::endl
                  << "in: " << std::endl << s << std::endl
                  << "out: " << std::endl << out
                  << std::endl;
        exit(1);
    }
}

int main(int argc, char ** argv) {
    std::vector<unsigned long> digits;
    for (int i = 1; i < argc; i++) {
        test_input(std::string{argv[i]});
    }

    
}
