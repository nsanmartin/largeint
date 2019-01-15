#include <tests.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <nat.hpp>
#include <limits>

//constexpr unsigned long ulong_max = std::numeric_limits<unsigned long>::max();


int main( int argc, char ** argv) {
    lint::nat n;
    unsigned long tnum{ulong_max / 2 + 1};
    std::cout << std::hex << tnum
              <<  "\t last bit:" << nth_bit(tnum, lint::BITS_IN_DIGIT -1)
              << std::endl;

}
