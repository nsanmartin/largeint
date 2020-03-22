#include <string>
#include <vector>
#include <iostream>
#include <natural.hpp>
#include <limits>
#include <sstream>

constexpr unsigned long ulong_max = std::numeric_limits<unsigned long>::max();


void test_input(std::string s) {
    std::cout << "reading " << s;

    lint::natural n{s};
    std::stringstream outss; outss << n;
    std::string out{outss.str()};

    std::size_t find {s.find_first_not_of('0')};
    if (find != std::string::npos) {
        s.erase(0, find);
    }

    if (s == out) {
        std::cout << " Ok\n";
    } else {
        std::cerr << "error reading number\n"
                  << "in: " << s
                  << "out: " << out
                  << '\n';
        exit(1);
    }
}

int main(int argc, char ** argv) {

    test_input("15f2c5da");
    test_input("f2acd3452345fbcda");
    test_input("2465364534ababaafaff");
    test_input("1410210a871fa66514f03821066295a0a988a727a463fa0358a6699af8753859afa46449");
    test_input("879049701ffa0803515ff845777438187a9a9ff36f4293882a223a26a92727f8a8f0a766798641663253556aa24674825561841a3f611f3097a07753");
    test_input("9110837a2a817f1541510f60f69f21873a619ff19fa78970a760292af99faf57722a77f7a4f5087f916a596549f7afa28045374a5904589f9a551395239");
}
