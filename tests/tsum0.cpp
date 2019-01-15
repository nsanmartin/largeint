#include <string>
#include <vector>
#include <iostream>
#include <nat.hpp>
#include <limits>

constexpr unsigned long ulong_max = std::numeric_limits<unsigned long>::max();


int main() {

    lint::nat n{std::vector<unsigned long>{
            ulong_max, ulong_max, ulong_max
                }};
    lint::nat m{std::vector<unsigned long>{1}};
    std::cout << n << std::endl;
    std::cout << m << std::endl;
    n += m;
    std::cout << n  << std::endl;

}
